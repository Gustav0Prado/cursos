#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#define tam 5
#define BK 4
#define UF 4

double timestamp (void)
{
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
  return ( (double) tp.tv_sec*1.0e3 + (double) tp.tv_nsec*1.0e-6 );
}

int main(){
   double teste[tam];
   double mat[tam][tam];
   double res[tam];
   double res2[tam];
   double t1, t2;

   for(int i = 0; i < tam; ++i){
      teste[i] = 2*i;
   }

   for(int i = 0; i < tam; ++i){
      for(int j = 0; j < tam; ++j){
         mat[i][j] = 2*(i+j);
      }
   }

   //Imprime matriz e vetor
   for(int i = 0; i < tam; ++i){
      for(int j = 0; j < tam; ++j){
         printf("%10g ", mat[i][j]);
      }
      printf("| %10g\n", teste[i]);
   }

   t1 = timestamp();
   for(int i = 0; i < tam; ++i){
      res[i] = 0.0;
      for(int j = 0; j < tam; ++j){
         res[i] += mat[i][j] * teste[j];
      }
   }
   t1 = timestamp() - t1;
   for(int i = 0; i < tam; ++i){
      printf("%g ", res[i]);
   }
   printf("\n");

   int istart, iend, jstart, jend;

   t2 = timestamp();
   for(int ii = 0; ii < tam/BK; ++ii){
      istart=ii*BK; iend=istart+BK;
      for(int jj = 0; jj < tam/BK; ++jj){
         jstart=jj*BK; jend=jstart+BK;
         for(int i = istart; i < iend; i+=UF){
            //res2[i] = 0.0;
            for(int j = jstart; j < jend; j++){
               res2[i]   += mat[i][j]   * teste[j];
               res2[i+1] += mat[i+1][j] * teste[j];
               res2[i+2] += mat[i+2][j] * teste[j];
               res2[i+3] += mat[i+3][j] * teste[j];
            }
         }
      }  
   }
   //Soma valores de fora dos blocos com os já calculados
   for(int ii = 0; ii<tam-tam%BK; ++ii){
   for(int jj=tam-tam%BK; jj<tam; ++jj){
      res2[ii] += mat[ii][jj] * teste[jj];
   }
   }

   //Multiplica linhas fora dos blocos
   for(int ii = tam-tam%BK; ii<tam; ++ii){
   res[ii] = 0.0;
   for(int jj=0; jj<tam; ++jj){
      res2[ii] += mat[ii][jj] * teste[jj];
   }
   }

   t2 = timestamp() - t2;
   for(int i = 0; i < tam; ++i){
      printf("%g ", res2[i]);
   }
   printf("\n");
}
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#define tam 4
#define BK 8
#define UF 8

double timestamp (void)
{
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
  return ( (double) tp.tv_sec*1.0e3 + (double) tp.tv_nsec*1.0e-6 );
}

void imprimeMatriz(double mat[tam][tam]){
   for(int i = 0; i < tam; ++i){
      for(int j = 0; j < tam; ++j){
         printf("%10g ", mat[i][j]);
      }
      printf("\n");
   }
}

int main(){
   double mat[tam][tam];
   double transp[tam][tam];
   double t1, t2;

   for(int i = 0; i < tam; ++i){
      for(int j = 0; j < tam; ++j){
         mat[i][j] = i+2*j;
      }
   }

   t1 = timestamp();
   
   for(int i = 0; i < tam; i++){
      for(int j = 0; j < tam; j++){
         transp[i][j] = mat[j][i];
      }
   }

   t1 = timestamp() - t1;
   imprimeMatriz(transp);
   printf("%g\n", t1);


   for(int i = 0; i < tam; i++){
      for(int j = 0; j < tam; j++){
         transp[i][j] = 0.0;
      }
   }

   //Blocking
   int istart, iend, jstart, jend, i, j;

   t2 = timestamp();
   for(int ii = 0; ii < tam/BK; ++ii){
      istart=ii*BK; iend=istart+BK;
      for(int jj = 0; jj < tam/BK; ++jj){
         jstart=jj*BK; jend=jstart+BK;
         for(i = istart; i < iend; i+=UF){
            for(j = jstart; j < jend; j++){
               transp[i][j]   = mat[j][i];
               transp[i+1][j] = mat[j][i+1];
               transp[i+2][j] = mat[j][i+2];
               transp[i+3][j] = mat[j][i+3];
               transp[i+4][j] = mat[j][i+4];
               transp[i+5][j] = mat[j][i+5];
               transp[i+6][j] = mat[j][i+6];
               transp[i+7][j] = mat[j][i+7];
            }
         }
      }
   }

   //residuo do blocking
   for(int ii = iend; ii < tam; ++ii){
      for(int jj = 0; jj < tam; ++jj){
         transp[ii][jj] = mat[jj][ii];
         transp[jj][ii] = mat[ii][jj];
      }
   }

   t2 = timestamp() - t2;
   imprimeMatriz(transp);
   printf("%g\n", t2);
}
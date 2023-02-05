#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

double timestamp (void)
{
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
  return ( (double) tp.tv_sec*1.0e3 + (double) tp.tv_nsec*1.0e-6 );
}

int main(){
   double teste[8];
   double res[8];
   double soma;
   double t1, t2, t3;

   for(int i = 0; i < 8; ++i){
      teste[i] = 2*i;
   }

   t1 = timestamp();
   for(int j = 0; j < 8; ++j){
      soma += teste[j];
   }
   t1 = timestamp() - t1;
   printf("%.15g\n", t1);

   t2 = timestamp();
   #pragma unroll 8
   for(int i = 0; i < 8; ++i){
      for(int j = 0; j < 8; j+=4){
         soma += teste[j];
      }
   }
   t2 = timestamp() - t2;
   printf("%.15g\n", t2);

   t3 = timestamp();
   for(int i = 0; i < 8; ++i){
      res[i] += teste[0];
      res[i] += teste[1];
      res[i] += teste[2];
      res[i] += teste[3];
      res[i] += teste[4];
      res[i] += teste[5];
      res[i] += teste[6];
      res[i] += teste[7];
   }
   t3 = timestamp() - t3;
   printf("%.15g\n", t3);
}
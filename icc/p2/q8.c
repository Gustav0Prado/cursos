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
   int n = 5;
   double A=1, B=2, C=3, D=4, E=5;
   double F[n*n];
   double G[n*n];
   double R[n*n];
   double RO[n*n];
   double tempo1, tempo2;

   for(int i = 0; i < n; ++i){
      F[i] = i;
   }

   for(int i = 0; i < n; ++i){
      G[i] = 2*i;
   }

   tempo1 = timestamp();

   for(int h = 0; h < pow(n, 2.0); h++) {
      R[h] = G[h] - A * F[h];
      if(h-1 >= 0){
         R[h] -= B * F[h - 1];
      }
      if(h+1 < pow(n, 2.0) - 1){
         R[h] -= C * F[h + 1];
      }
      if(h - n >= 0){
         R[h] -= D * F[h - n];
      }
      if(h + n < pow(n, 2.0) - 1){
         R[h] -= E * F[h + n];
      }
   }

   tempo1 = timestamp() - tempo1;

   tempo2 = timestamp();

   // for(int h = 0; h < n*n; h++) {
   //    RO[h] = G[h] - A * F[h];
   //    RO[h] -= C * F[h + 1];
   // }
   // for(int h = 1; h < n*n; h++) {
   //    RO[h] -= B * F[h - 1];
   // }
   // for(int h = n; h < n*n; h++) {
   //    RO[h] -= D * F[h - n];
   // }
   // for(int h = 0; h < (n*n) - n-1; h++) {
   //    RO[h] -= E * F[h + n];
   // }

   for(int h = 0; h < n*n; h++) {
      RO[h] = G[h] - A * F[h];
      RO[h] - C * F[h + 1];
   }
   for(int h = 1; h < n*n; h++) {
      RO[h] -= B * F[h - 1];
   }
   for(int h = n; h < n*n; h++) {
      RO[h] -= D * F[h - n];
   }
   for(int h = 0; h < (n*n) - n-1; h++) {
      RO[h] -= E * F[h + n];
   }

   tempo2 = timestamp() - tempo2;

   for(int i = 0; i < n; ++i){
      printf("%4g ", R[i]);
   }
   printf("-- %g\n", tempo1);

   for(int i = 0; i < n; ++i){
      printf("%4g ", RO[i]);
   }
   printf("-- %g\n", tempo2);
}
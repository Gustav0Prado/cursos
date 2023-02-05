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
   int i,j;
   int n = 600;

   double a[n][n];
   double ao[n][n];
   double x[n];
   double y[n];
   double cosval[8];
   double t1, t2;

   ///////////////////////////////////////////

   t1 = timestamp();

   for (i=0; i<n; i++){
      for (j=0; j<n; j++)
         a[j][i] = x[i] + y[j] * cos((i%8)*M_PI/7.0);
   }

   t1 = timestamp() - t1;

   ///////////////////////////////////////////

   t2 = timestamp();

   for(int i = 0; i < 8; ++i){
      cosval[i] = cos(i*M_PI/7.0);
   }

   
   for (j=0; j<n; j++){
      for (i=0; i<n; i++)
         ao[j][i] = x[i] + y[j] * cosval[i%8];
   }

   t2 = timestamp() - t2;

   ///////////////////////////////////////////

   // for(int i = 0; i<n; ++i){
   //    for(int j = 0; j<n; ++j){
   //       printf("%g ", a[i][j]);
   //    }
   //    printf("\n");
   // }
   printf("-- %g --\n\n", t1);

   // for(int i = 0; i<n; ++i){
   //    for(int j = 0; j<n; ++j){
   //       printf("%g ", ao[i][j]);
   //    }
   //    printf("\n");
   // }
   printf("-- %g --\n", t2);
}

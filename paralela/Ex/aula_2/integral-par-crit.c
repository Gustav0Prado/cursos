#include <stdio.h>
#include <omp.h>

#define MAX_THREADS 4
#define num_steps 1000000 * 1 
#define num_steps_thread num_steps/MAX_THREADS

double step;

int main() {
   double res = 0.0;

   #pragma omp parallel num_threads(MAX_THREADS)
   {
      int i; double x, sum = 0.0;

      int ID = omp_get_thread_num();
      int start = ID*num_steps_thread;
      int end   = num_steps_thread*(ID+1);

      step = 1.0/(double) num_steps;
      for(i = start; i < end; ++i) {
         x = (i + 0.5) * step; // Largura do retangulo
         sum = sum + 4.0 / (1.0 + x*x); // Sum += Area do retangulo
      }
      #pragma omp critical
         res += sum * step;
   }
   
   printf("Resultado Paralelo: %.15f\n", res);
}
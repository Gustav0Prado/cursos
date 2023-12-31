#include <stdio.h>
#include <omp.h>

#define MAX_THREADS 4
#define num_steps 1000000 * 1 

double step;

int main() {
   int i; double res = 0.0;

   #pragma omp parallel num_threads(MAX_THREADS)
   {
      int i; double x, sum = 0.0;
      step = 1.0/(double) num_steps;

      #pragma omp for
         for(i = 0; i < num_steps; ++i) {
            x = (i + 0.5) * step; // Largura do retangulo
            sum = sum + 4.0 / (1.0 + x*x); // Sum += Area do retangulo
         }
         #pragma omp critical
            res += sum * step;
   }
   
   printf("Resultado Paralelo: %.15f\n", res);
}
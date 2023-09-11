#include <stdio.h>

static long num_steps = 1000000 * 10;
double step;

int main() {
   double pi, sum = 0.0;
   step = 1.0/(double) num_steps;

   #pragma omp parallel num_threads(4)
   {
      double x;
      
      #pragma omp for
      for(int i = 0; i < num_steps; ++i) {
         x = (i + 0.5) * step; // Largura do retangulo
         sum = sum + 4.0 / (1.0 + x*x); // Sum += Area do retangulo
      }
      #pragma omp critical
         pi = step * sum;
   }

   printf("Resultado Sequencial: %.15f\n", pi);
}
#include <stdio.h>

static long num_steps = 1000000 * 10;
double step;

int main() {
   double pi;
   step = 1.0/(double) num_steps;

   #pragma omp parallel
   {
      double x, sum = 0.0;

      #pragma omp for reduction (*:pi)
         for(int i = 0; i < num_steps; ++i) {
            x = (i + 0.5) * step; // Largura do retangulo
            sum = sum + 4.0 / (1.0 + x*x); // Sum += Area do retangulo
         }
         pi += step * sum;
   }

   printf("Resultado Sequencial: %.15f\n", pi);
}
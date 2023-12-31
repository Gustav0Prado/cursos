#include <stdio.h>

static long num_steps = 1000000 * 1;
double step;

int main() {
   int i; double x, pi, sum = 0.0;

   step = 1.0/(double) num_steps;
   for(i = 0; i < num_steps; ++i) {
      x = (i + 0.5) * step; // Largura do retangulo
      sum = sum + 4.0 / (1.0 + x*x); // Sum += Area do retangulo
   }
   pi = step * sum;

   printf("Resultado Sequencial: %.15f\n", pi);
}
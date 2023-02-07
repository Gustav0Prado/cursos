#include <stdio.h>
#include <math.h>

int main(){
   int n;
   double xint;

   printf("Insira a qtd de pontos: ");
   scanf("%d", &n);

   double x[n];
   double y[n];
   double tab[n][n];

   printf("Insira os valores de x: ");
   for(int i = 0; i < n; ++i){
      scanf("%lg", &x[i]);
   }

   printf("Insira os valores de y: ");
   for(int i = 0; i < n; ++i){
      scanf("%lg", &y[i]);
   }

   printf("Insira o valor de x a ser interpolado: ");
   scanf("%lg", &xint);

   //matriz de diferencas divididas
   //linha 1 = f(xi)
   for(int i = 0; i < n; ++i){
      tab[0][i] = y[i];
   }
   //constroi as outras linhas
   for(int i = 1; i < n; ++i){
      for(int j = 0; j < n-i; ++j){
         tab[i][j] = (tab[i-1][j+1] - tab[i-1][j]) / (x[j+i]-x[j]);
      }
   }

   printf("\n");
   for(int i = 0; i < n; ++i){
      for(int j = 0; j < n-i; ++j){
         printf("%15.7f ", tab[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   double soma = 0.0;
   //calcula valor do polinomio
   for(int i = 0; i < n; ++i){
      double d = tab[i][0];
      double mult = 1.0;

      for(int j = 0; j < i; ++j){
         mult *= (xint - x[j]);
      }

      soma += d*mult;
   }

   printf("P(x) = %g\n", soma);
}
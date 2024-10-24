#include <stdio.h>
#include <math.h>

int main(){
   int n, h;
   double xint;

   printf("Insira a qtd de pontos: ");
   scanf("%d", &n);

   double x[n];
   double y[n];
   double tab[n][n];

   printf("Insira a distancia entre os pontos: ");
   scanf("%d", &h);

   printf("Insira o ponto inicial: ");
   scanf("%lg", &x[0]);
   for(int i = 1; i < n; ++i){
      x[i] = x[0]+(i*h);
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
         tab[i][j] = (tab[i-1][j+1] - tab[i-1][j]);
      }
   }

   // // Imprime a tabela
   // printf("\n");
   // for(int i = 0; i < n; ++i){
   //    for(int j = 0; j < n-i; ++j){
   //       printf("%15.7f ", tab[i][j]);
   //    }
   //    printf("\n");
   // }
   // printf("\n");

   double soma = tab[0][0];
   double mult = 1.0;
   double div = 1.0;
   double d;
   //calcula valor do polinomio
   for(int i = 1; i < n; ++i){
      d = tab[i][0];

      mult *= (xint - x[i-1]);
      div *= (h*i);

      soma += (d/div)*mult;
   }

   printf("P(x) = %g\n", soma);
}
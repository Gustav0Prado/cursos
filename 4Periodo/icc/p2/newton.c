#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

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
   double d;
   //calcula valor do polinomio
   for(int i = 1; i < n; ++i){
      d = tab[i][0];

      mult *= (xint - x[i-1]);

      soma += d*mult;
   }

   printf("P(x) = %g\n", soma);

   double soma2[4];
   double mult2[4];
   double d2[4];

   soma2[0] = 0.0;
   soma2[1] = 0.0;
   soma2[2] = 0.0;
   soma2[3] = 0.0;

   mult2[0] = 1.0;
   mult2[1] = 1.0;
   mult2[2] = 1.0;
   mult2[3] = 1.0;

   soma = tab[0][0];
   //calcula valor do polinomio
   for(int i = 1; i < n-(n%4)-1; i+=4){
      d2[0] = tab[i][0];
      d2[1] = tab[i+1][0];
      d2[2] = tab[i+2][0];
      d2[3] = tab[i+3][0];

      for(int j = 0; j < i; ++j){
         mult2[0] *= (xint - x[j]);
      }
      for(int j = 0; j < i+1; ++j){
         mult2[1] *= (xint - x[i]);
      }
      for(int j = 0; j < i+2; ++j){
         mult2[2] *= (xint - x[i-1]);
      }
      for(int j = 0; j < i+3; ++j){
         mult2[3] *= (xint - x[i-1]);
      }

      soma2[0] += d2[0]*mult2[0];
      soma2[1] += d2[1]*mult2[1];
      soma2[2] += d2[2]*mult2[2];
      soma2[3] += d2[3]*mult2[3];
   }

   soma += soma2[0]+soma2[1]+soma2[2]+soma2[3];
   
   //residuo do unroll
   mult = 1.0;
   for(int i = n-(n%4)-1; i < n; ++i){
      d = tab[i][0];

      mult *= (xint - x[i-1]);

      soma += d*mult;
   }

   printf("P(x) com unroll = %g\n", soma);
}
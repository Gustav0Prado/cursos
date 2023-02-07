#include <stdio.h>
#include <math.h>

int main(){
   int n, p;

   printf("Insira a qtd de pontos: ");
   scanf("%d", &n);
   
   printf("Insira a qtd de termos do polinomio: ");
   scanf("%d", &p);

   double x[n];
   double y[n];

   double A[p][p];
   double B[p];

   printf("Insira os pontos x: ");
   for(int i = 0; i < n; ++i){
      scanf("%lg", &x[i]);
   }

   printf("Insira os pontos y: ");
   for(int i = 0; i < n; ++i){
      scanf("%lg", &y[i]);
   }

   //calcula valores de dentro da matriz
   for(int i = 0; i < p; ++i){
      for(int j = i; j < p; ++j){
         //somatorio
         double soma = 0.0;
         for(int k = 0; k < n; ++k){
            double xi = 1.0;
            for(int m = 0; m < j+i; ++m){
               xi *= x[k];
            }
            soma += xi;
         }
         A[i][j] = soma;

         //ajusta outros elementos identicos
         int ik = i+1;
         int jk = j-1;
         while( ik < n && jk >= 0){
            A[ik][jk] = soma;
            ik++;
            jk--;
         }
         // A[i][j] = soma;
         // A[j][i] = soma;
      }


      //Calcula valores dos termos independentes
      double somay = 0.0;
      for(int k = 0; k < n; ++k){
         double xi = 1.0;
         for(int m = 0; m < i; ++m){
            xi *= x[k];
         }
         somay += y[k]*xi;
      }
      B[i] = somay;
   }

   //Imprime sistema linear resultante
   for(int i = 0; i < p; ++i){
      for(int j = 0; j < p; ++j){
         printf("%15g ", A[i][j]);
      }
      printf(" |%15g\n", B[i]);
   }
}
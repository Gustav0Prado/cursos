#include <stdio.h>
#include <math.h>

int main(){
   int n;
   double xint;

   printf("Insira a qtd de pontos: ");
   scanf("%d", &n);

   double x[n];
   double y[n];

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

   // //Metodo de Lagrange
   // double Px, Li, xi, xj, fi;
   // Px = 0.0;

   // for(int i = 0; i < n; ++i){
   //    Li = 1.0;
   //    xi = x[i];
   //    for(int j = 0; j < i; ++j){
   //       xj = x[j];
   //       Li *= (xint - xj)/(xi - xj);
   //    }
   //    printf("%g\n", Li);

   //    for(int j = i+1; j < n; ++j){
   //       xj = x[j];
   //       Li *= (xint - xj)/(xi - xj);
   //    }
   //    printf("%g\n", Li);

   //    Px += Li*y[i]; 
   // }

   int j;
   double Px, Li, xi, xj;
   double x_temp[4]; 
   Px = 0.0;

   //Metodo de Lagrange com vetorização
   for(int i = 0; i < n; ++i){
      Li = 1.0;
      xi = x[i];

      double L_temp[4] = {1.0, 1.0, 1.0, 1.0};
      //0 -> i-1
      for(j = 0; j < i-i%4; j+=4){
        for(int k = 0; k < 4; ++k){
         L_temp[k] *= (xint - x[j+k])/(xi - x[j+k]);
        }
      }
      Li *= L_temp[0] * L_temp[1] * L_temp[2] * L_temp[3];
      //residuo
      for(j; j < i; ++j){
         xj = x[j];
         Li *= (xint - xj)/(xi - xj);
      }

      L_temp[0] = 1.0;
      L_temp[1] = 1.0;
      L_temp[2] = 1.0;
      L_temp[3] = 1.0;
      for(j = i+1; j < n-4+1; j+=4){
         for(int k = 0; k < 4; ++k){
            L_temp[k] *= (xint - x[j+k])/(xi - x[j+k]);
         }
      }
      Li *= L_temp[0] * L_temp[1] * L_temp[2] * L_temp[3];
      //residuo
      for(j; j < n; ++j){
         xj = x[j];
         Li *= (xint - xj)/(xi - xj);
      }

      Px += Li*y[i]; 
   }

   // //Lagrange com unroll
   // for(int i = 0; i < n; ++i){
   //    Li = 1.0;
   //    xi = x[i];

   //    double L_temp[4] = {1.0, 1.0, 1.0, 1.0};
   //    //0 -> i-1
   //    for(j = 0; j < i-i%2; j+=2){
   //       // xj = x[j];
   //       // Li *= (xint - xj)/(xi - xj);

   //       x_temp[0] = x[j];
   //       x_temp[1] = x[j+1];

   //       L_temp[0] *= (xint - x_temp[0])/(xi - x_temp[0]);
   //       L_temp[1] *= (xint - x_temp[1])/(xi - x_temp[1]);
   //    }
   //    Li *= L_temp[0] * L_temp[1];
   //    //residuo
   //    for(j; j < i; ++j){
   //       xj = x[j];
   //       Li *= (xint - xj)/(xi - xj);
   //    }

   //    L_temp[0] = 1.0;
   //    L_temp[1] = 1.0;
   //    for(j = i+1; j < n-2+1; j+=2){
   //       // xj = x[j];
   //       // Li *= (xint - xj)/(xi - xj);

   //       x_temp[0] = x[j];
   //       x_temp[1] = x[j+1];

   //       L_temp[0] *= (xint - x_temp[0])/(xi - x_temp[0]);
   //       L_temp[1] *= (xint - x_temp[1])/(xi - x_temp[1]);
   //    }
   //    Li *= L_temp[0] * L_temp[1];
   //    //residuo
   //    for(j; j < n; ++j){
   //       xj = x[j];
   //       Li *= (xint - xj)/(xi - xj);
   //    }

   //    Px += Li*y[i]; 
   // }

   printf("P(x) = %.4g\n", Px);
}
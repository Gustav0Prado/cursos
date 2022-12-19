#include "oper.h"
#include <stdio.h>

//Multiplica dois vetores (produto escalar)
double multVetVet(double *v1, double *v2, int n){
   double soma = 0.0f;

   for(int i = 0; i < n; ++i){
      soma += v1[i]*v2[i];
   }

   return soma;
}

//Soma cada elemento de um vetor v1 com de o v2 multiplicado por m, devolve um vetor res
// res = v1 +m*v2
void somaVetVet(double *v1, double m, double *v2, double *res, int n){
   for(int i = 0; i < n; ++i){
      res[i] = v1[i] + m*v2[i];
   }
}

//Multiplica uma Matriz por um vetor
// res = A*v
void multMatVet(double **A, double *v, double *res, int n){
   for(int i = 0; i < n; ++i){
      res[i] = 0.0f;
      for(int j = 0; j < n; ++j){
         res[i] += A[i][j]*v[j];
      }
   }
}

//Multiplica um vetor v1 com uma matriz, e o vetor resultante é multiplicado com um vetor v2
//retorna v1*A*v2
double multVetMatVet(double *v1, double **A, double *v2, int n){
   double aux[n];

   multMatVet(A, v1, aux, n);

   //retorna a multiplicacao do vetor resultante com o segundo vetor
   return multVetVet(aux, v2, n);
}

//Multiplica o vetor v2 e a matriz A, e os valores vetor resultante, multiplicados por m, são somados com os valores de v1
//res = v1 + mAv2
void somaVetMatxVet(double **A, double *v1, double *v2, double m, double *res, int n){
   double vNovo[n];
   multMatVet(A, v2, vNovo, n);

   for(int i = 0; i < n; ++i){
      res[i] = v1[i] + m*vNovo[i];
   }
}
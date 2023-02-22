//Gustavo do Prado Silva - 20203942 
//Rafael Gonçalves dos Santos - 20211798

#include "oper.h"
#include "sistema.h"
#include "utils.h"
#include "metodos.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <likwid.h>

#define UNROLL 4

//Multiplica matriz simetrica com vetor
void multMatSimVet(SistLinear_t *restrict SL, double *restrict vet, double *restrict res, int n){
   /* multiplica com vetor */
   int k = SL->k;

   for (int i = 0; i < n; ++i) {
      int maxj = SL->Sim.jend[i]-SL->Sim.jstart[i]+1;
      for(int j = 0; j < maxj; ++j){
         res[i] += SL->Sim.A[k*i+j] * vet[SL->Sim.jstart[i]+j];
      }
   }

   /* multiplica valores simetricos com vetor */
   for (int i = 1; i < n; ++i) {
      int ii = i-1;
      int jj = 1;

      while(jj < SL->k && ii >= 0){
         res[i] += SL->Sim.A[k*ii+jj] * vet[ii];
         ii--;
         jj++;
      }
   }
}

//Multiplica dois vetores (produto escalar)
double multVetVet(double *restrict v1, double *restrict v2, int n){
   double soma = 0.0f;

   for(int i = 0; i < n-n%UNROLL; i+=UNROLL){
      soma += v1[i]*v2[i]     + v1[i+1]*v2[i+1] +
              v1[i+2]*v2[i+2] + v1[i+3]*v2[i+3];
   }
   for(int i = n-n%UNROLL; i < n; ++i)
      soma += v1[i]*v2[i];

   return soma;
}

//Multiplica dois vetores, um deles como se fosse a diagonal de uma matriz e o outro normalmente
void multVetVetDiagonal (double *restrict vetDiagonal, double *restrict v2, double *restrict res, int n) {
   for (int i = 0; i < n; ++i) {
      res[i] = vetDiagonal[i] * v2[i];
   }
}

//Soma cada elemento de um vetor v1 com de o v2 multiplicado por m, devolve um vetor res
// res = v1 +m*v2
void somaVetVet(double *restrict v1, double m, double *restrict v2, double *restrict res, int n){
   for(int i = 0; i < n; ++i)
      res[i] = v1[i] + m*v2[i];
}

//Multiplica um vetor v1 com uma matriz, e o vetor resultante é multiplicado com um vetor v2
//retorna v1*A*v2
double multVetMatVet(double *v1, SistLinear_t *restrict SL, double *v2, int n){
   double *aux = malloc(n*sizeof(double));
   memset(aux, 0, n*sizeof(double));

   multMatSimVet(SL, v1, aux, n);

   //retorna a multiplicacao do vetor resultante com o segundo vetor
   double retorno = multVetVet(aux, v2, n);

   free(aux);

   return retorno;
}

//Multiplica o vetor v2 e a matriz A, e os valores vetor resultante, multiplicados por m, são somados com os valores de v1
//res = v1 + mAv2
void somaVetMatxVet(SistLinear_t *restrict SL, double *restrict v1, double *restrict v2, double m, double *restrict res, int n){
   double *aux = malloc(n*sizeof(double));
   memset(aux, 0, n*sizeof(double));

   multMatSimVet(SL, v2, aux, n);

   for(int i = 0; i < n; ++i){
      res[i] = v1[i] + m*aux[i];
   }

   free(aux);
}

// Encontra a maior diferenca relativa entre as respostas subsequentes
// retorna max ( |xi - xi-1| / |xi| )
double normamax (double *restrict v1, double *restrict v2, int n){
   double diff;
   double maior = 0.0;

   for (int i = 0; i < n; i++) {
      diff = ( ABS(v1[i] - v2[i]) / ABS(v1[i]) );
      if (diff > maior)
         maior = diff;
   }

   return maior;
}  

// Encontra a maior diferenca absoluta entre as respostas subsequentes
// retorna max ( |xi - xi-1| )
double normamaxAbs (double *restrict v1, double *restrict v2, int n){
   double diff;
   double maior = 0.0;

   for (int i = 0; i < n; i++) {
      diff = ( ABS(v1[i] - v2[i]));
      if (diff > maior)
         maior = diff;
   }

   return maior;
}

//Calcula residuo do sistema tridiagonal
double residuoDiag(SistLinear_t *restrict SL, double *restrict b, double *restrict x, double *restrict r, double *restrict tempR){
   LIKWID_MARKER_REGISTER("op2-v2");
   LIKWID_MARKER_START("op2-v2");

   int n = SL->n;
   int k = SL->k;

   *tempR = timestamp();

   /* Primeiras linhas começam deslocadas pra direita */
   for(int i = 0; i < k/2; ++i){
      int m = 0;
      for(int j = k/2-i; j < k; ++j){
         r[i] += SL->Diag.A[k*i+j] * x[m];
         m++;
      }
      r[i] -= SL->Diag.b[i];
   }

   /* Usando os valores direto */
   for(int i = k/2; i < n; ++i){
      int js = SL->Diag.jstart[i];
      for(int j = js; j <= SL->Diag.jend[i]; ++j){
         r[i] += SL->Diag.A[k*i+(j-js)] * x[j];
      }
      r[i] -= SL->Diag.b[i];
   }

   double ret = normaL2(r, n);

   LIKWID_MARKER_STOP("op2-v2");
   *tempR = timestamp() - *tempR;

   return ret;
}
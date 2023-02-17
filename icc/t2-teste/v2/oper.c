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

//Multiplica matriz simetrica com vetor
void multMatSimVet(SistLinear_t *SL, double *vet, double *res, int n){
   /* multiplica com vetor */
   int k = SL->k;

   for (int i = 0; i < n; ++i) {
      int maxj = SL->Sim.jend[i]-SL->Sim.jstart[i]+1;
      for(int j = 0; j < maxj; ++j){
         res[i] += SL->Sim.A[i][j] * vet[SL->Sim.jstart[i]+j];
      }
   }

   /* multiplica valores simetricos com vetor */
   for (int i = 1; i < n; ++i) {
      int ii = i-1;
      int jj = 1;

      while(jj < SL->k && ii >= 0){
         res[i] += SL->Sim.A[ii][jj] * vet[ii];
         ii--;
         jj++;
      }
   }
}

//Multiplica dois vetores (produto escalar)
double multVetVet(double *v1, double *v2, int n){
   double soma = 0.0f;

   for(int i = 0; i < n; ++i){
      soma += v1[i]*v2[i];
   }

   return soma;
}
// Multiplica duas matrizes de mesma ordem
void multMatMat (double **m1, double **m2, double **mRes, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      mRes[i][j] = 0.0;
      for (int k = 0; k < n; k++) {
        mRes[i][j] = mRes[i][j] + (m1 [i][k] * m2[k][j]);
      }
    }
  }
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
double multVetMatVet(double *v1, SistLinear_t *SL, double *v2, int n){
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
void somaVetMatxVet(SistLinear_t *SL, double *v1, double *v2, double m, double *res, int n){
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
double normamax (double *v1, double *v2, int n){
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
double normamaxAbs (double *v1, double *v2, int n){
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
double residuoDiag(SistLinear_t *SL, double *b, double *x, double *r){
   LIKWID_MARKER_REGISTER("op2-v2");
   LIKWID_MARKER_START("op2-v2");

   int n = SL->n;
   int k = SL->k;

   double tempoR = timestamp();

   for(int i = 0; i < n; ++i){
      for(int j = 0; j < n; ++j){
         r[i] += getDiag(SL->Diag.A, i, j, k) * x[j];
      }
      r[i] = SL->Diag.b[i] - r[i];
   }

   LIKWID_MARKER_STOP("op2-v2");

   return timestamp() - tempoR;
}
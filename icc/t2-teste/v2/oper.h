//Gustavo do Prado Silva - 20203942 
//Rafael Gonçalves dos Santos - 20211798

#include "sistema.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <likwid.h>

#ifndef __OPER_H__
#define __OPER_H__

#define UNROLL 4
#define getDiagA(A, i, j, n, k) ( (j-i > (k/2) || j-i < -(k/2)) ? 0.0 : A[k*i+((k/2)+(j-i))] )

//Multiplica matriz simetrica com vetor
static inline void multMatSimVet(SistLinear_t *restrict SL, double *restrict vet, double *restrict res, int n){
   /* multiplica com vetor */
   int k = SL->k;

   for (int i = 0; i < n; ++i) {
      /* multiplica considerando o deslocamento de cada linha */
      int maxj = SL->Sim.jend[i]-SL->Sim.jstart[i]+1;
      for(int j = 0; j < maxj; ++j){
         res[i] += SL->Sim.A[k*i+j] * vet[SL->Sim.jstart[i]+j];
      }
   }

   /* multiplica valores simetricos com vetor */
   for (int i = 1; i < n; ++i) {
      /* A partir da primeira linha, valores antes da diagonal principal sao simetricos */
      for(int jj = 1; jj < SL->k && i-jj >= 0; ++jj){
         int ii = i-jj;
         res[i] += SL->Sim.A[k*ii+jj] * vet[ii];
      }
   }
}

//Multiplica dois vetores (produto escalar)
static inline double multVetVet(double *restrict v1, double *restrict v2, int n){
   double soma = 0.0;
   double soma2 = 0.0;
   double somaTemp[UNROLL] = {0.0, 0.0, 0.0, 0.0};

   for(int i = 0; i < n-(n%UNROLL); i+=UNROLL){
      somaTemp[0] += v1[i]  *v2[i];
      somaTemp[1] += v1[i+1]*v2[i+1];
      somaTemp[2] += v1[i+2]*v2[i+2];
      somaTemp[3] += v1[i+3]*v2[i+3];
   }
   soma = somaTemp[0]+somaTemp[1]+somaTemp[2]+somaTemp[3];
   for(int i = n-(n%UNROLL); i < n; i++){
      soma += v1[i]*v2[i];
   }

   return soma;
}

//Multiplica dois vetores, um deles como se fosse a diagonal de uma matriz e o outro normalmente
static inline void mulVetVetDiagonal (double *restrict vetDiagonal, double *restrict v2, double *restrict res, int n) {
   for (int i = 0; i < n-n%UNROLL; i+=UNROLL){
      res[i]   = vetDiagonal[i] * v2[i];
      res[i+1] = vetDiagonal[i+1] * v2[i+1];
      res[i+2] = vetDiagonal[i+2] * v2[i+2];
      res[i+3] = vetDiagonal[i+3] * v2[i+3];
   }
   for (int i = n-n%UNROLL; i < n; i++){
      res[i] = vetDiagonal[i] * v2[i];
   }
}

//Soma cada elemento de um vetor v1 com de o v2 multiplicado por m, devolve um vetor res
// res = v1 +m*v2
static inline void somaVetVet(double *restrict v1, double m, double *restrict v2, double *restrict res, int n){
   for (int i = 0; i < n-n%UNROLL; i+=UNROLL){
      res[i]   = v1[i]   + m*v2[i];
      res[i+1] = v1[i+1] + m*v2[i+1];
      res[i+2] = v1[i+2] + m*v2[i+2];
      res[i+3] = v1[i+3] + m*v2[i+3];
   }
   for (int i = n-n%UNROLL; i < n; i++){
      res[i] = v1[i] + m*v2[i];
   }
}

//Multiplica um vetor v1 com uma matriz, e o vetor resultante é multiplicado com um vetor v2
//retorna v1*A*v2
static inline double multVetMatVet(double *restrict v1, SistLinear_t *restrict SL, double *restrict v2, int n){
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
static inline void somaVetMatxVet(SistLinear_t *restrict SL, double *restrict v1, double *restrict v2, double m, double *restrict res, int n){
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
static inline double normamax (double *restrict v1, double *restrict v2, int n){
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
static inline double normamaxAbs (double *restrict v1, double *restrict v2, int n){
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
static inline double residuoDiag(SistLinear_t *restrict SL, double *restrict b, double *restrict x, double *restrict r){
   LIKWID_MARKER_REGISTER("op2-v2");
   LIKWID_MARKER_START("op2-v2");

   int n = SL->n;
   int k = SL->k;

   double *res = malloc(n*sizeof(double));
   memset(res, 0, n*sizeof(double));

   double tempoR = timestamp();

   /* UNROLL DE TAMANHO 4 */
   for(int i = 0; i < n-n%UNROLL; i+=UNROLL){
      for(int j = 0; j < n; ++j){
         r[i]   += getDiagA(SL->Diag.A, i, j, n, k)   * x[j];
         r[i+1] += getDiagA(SL->Diag.A, (i+1), j, n, k) * x[j];
         r[i+2] += getDiagA(SL->Diag.A, (i+2), j, n, k) * x[j];
         r[i+3] += getDiagA(SL->Diag.A, (i+3), j, n, k) * x[j];
      }
      r[i]   -= SL->Diag.b[i];
      r[i+1] -= SL->Diag.b[i+1];
      r[i+2] -= SL->Diag.b[i+2];
      r[i+3] -= SL->Diag.b[i+3];
   }

   for(int i = n-n%UNROLL; i < n; ++i){
      for(int j = 0; j < n; ++j){
         r[i] += getDiagA(SL->Diag.A, i, j, n, k) * x[j];
      }
      r[i] -= SL->Diag.b[i];
   }

   LIKWID_MARKER_STOP("op2-v2");

   return timestamp() - tempoR;
}

#endif
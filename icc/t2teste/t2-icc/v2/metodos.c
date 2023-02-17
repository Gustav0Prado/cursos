//Gustavo do Prado Silva - 20203942 
//Rafael Gonçalves dos Santos - 20211798

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "oper.h"
#include "sistema.h"
#include "utils.h"

//calcula norma L2 do residuo
double normaL2(double *r, int n){
   double soma = 0.0;
   for(int i = 0; i < n; ++i){
      soma += r[i]*r[i];
   }

   return sqrt(soma);
}

void simetrizaSistema (SistLinear_t *SL) {
   double **M_trans = malloc(SL->k * sizeof(double *));
   
   int k = SL->k;
   int n = SL->n;

   if(!M_trans){
      fprintf(stderr, "Erro de alocação!\n");
      exit(ERRALLOC);
   }

   // inicializa as duas matrizes
   // cria a matriz trasnposta
   for (int i = 0; i < SL->k; i++) {
      M_trans[i] = malloc(sizeof(double)*SL ->n);
      memset(M_trans[i], 0, SL->n*sizeof(double));

      /* Cria matriz k*n transposta */
      for(int j = 0; j < SL->n; ++j){
         M_trans[i][j] = SL->Diag.A[j][i];
      }
   }
   
   /* Cria matriz simetrica, com apenas diagonais da principal para cima
      Para cada coluna (i), calcula a linha (j)
      Cada coluna vai representar uma diagonal
      Na multiplicação, leva em conta o deslocamento (m) da linha, assim nao precisa calcular
      com os 0s (que nao estao nas matrizes)
   */
   for(int i = 0; i < k; ++i){
      for(int j = 0; j < n-i; ++j){
         SL->Sim.A[j][i] = 0.0;
         int m = SL->Diag.jstart[j+i]-SL->Diag.jstart[j];
         int l = 0;
         
         while(m < k){
            SL->Sim.A[j][i] += SL->Diag.A[j][m] * M_trans[l][j+i];
            ++m;
            ++l;
         }
      }
   }

   /* Salva inicio e final de cada linha da matriz simetrica*/
   for(int i = 0; i <= n-k; ++i){
      SL->Sim.jstart[i] = i;
      SL->Sim.jend[i] = k+i-1;
   }
   for(int i = n-k+1; i < n; ++i){
      SL->Sim.jstart[i] = i;
      SL->Sim.jend[i] = n-1;
   }

   // At * b
   /*
      Multiplica cada coluna da transposta por b[i], levando em conta 
      o deslocamento que cada linha deveria ter (m)
   */
   for(int i = 0; i < n; ++i){
      int m = SL->Diag.jstart[i];
      for(int j = 0; (j < k) && (m+j < n); ++j){
         SL->Sim.b[m+j] += M_trans[j][i] * SL->Diag.b[i];
      }
   }

   // libera as estruturas
   for (int i = 0; i < SL->k; i++){
      free (M_trans[i]);
   }
   free (M_trans);
}

//Realiza método do gradiente conjugado e retorna o tempo médio levado pelas iterações
//Criterio de parada eh apenas o num de iteracoes
double GradConjIt(SistLinear_t *SL, double *x, double **M, FILE *arq){
   double *r  = malloc(sizeof(double)*SL->n);
   double *r1 = malloc(sizeof(double)*SL->n);
   double *z  = malloc(sizeof(double)*SL->n);
   double *z1 = malloc(sizeof(double)*SL->n);
   double *p  = malloc(sizeof(double)*SL->n);
   double *p1 = malloc(sizeof(double)*SL->n);
   double *x1 = malloc(sizeof(double)*SL->n);
   
   double alpha, beta;

   if(!r || !r1 || !z || !z1 || !p || !p1 || !x1){
      fprintf(stderr, "Erro de alocação!\n");
      exit(ERRALLOC);
   }

   double tempo = timestamp();

   //calcula R0
   somaVetMatxVet(SL, SL->Sim.b, x, -1, r, SL->n);

   //z0 := M^(-1)*r
   multMatVet(M, r, z, SL->n);

   //p0 = z0
   memcpy(p, z, SL->n * sizeof(double));

   prnSisLinSim(SL);

   for(int iter = 0; iter < SL->i; ++iter){
      //alpha(k) := r(k)T*z(k) / p(k)T*A*p(k)
      alpha = (multVetVet(r, z, SL->n))/(multVetMatVet(p, SL, p, SL->n));
      if(isnan(alpha) || isinf(alpha)){
         break;
      }

      //x(k+1) := x(k) + a(k)*p(k)
      somaVetVet(x, alpha, p, x1, SL->n);

      //r(k+1) := r(k) - a(k)*A*p(k)
      somaVetMatxVet(SL, r, p, -alpha, r1, SL->n);

      //z(k+1) := M^(-1)*r1(k+1)
      multMatVet(M, r1, z1, SL->n);

      //beta(k) := r(k+1)T*z(k+1) / r(k)T*z(k)
      beta = multVetVet(r1, z1, SL->n) / multVetVet(r, z, SL->n);
      if(isnan(beta) || isinf(beta)){
         break;
      }

      //p(k+1) := z(k+1) + beta*p(k)
      somaVetVet(z1, beta, p, p1, SL->n);

      //Escreve na saida a normamax da iteração
      fprintf(arq, "# iter %d: %.15g\n", iter+1, normamaxAbs(x1, x, SL->n));

      //r = r1
      memcpy(r, r1, SL->n * sizeof(double));
      //x = x1
      memcpy(x, x1, SL->n * sizeof(double));
      //pk = pk1
      memcpy(p, p1, SL->n * sizeof(double));
      //z = z1
      memcpy(z, z1, SL->n * sizeof(double));
   }

   free(x1);
   free(r);
   free(r1);
   free(z);
   free(z1);
   free(p);
   free(p1);

   //retorna tempo medio por iteração
   return (timestamp()-tempo) / SL->i;
}

//Realiza método do gradiente conjugado e retorna o tempo médio levado pelas iterações
//Criterio de parada eh o erro definido e o num de iteracoes
double GradConjErr(SistLinear_t *SL, double *x, double **M, double err, FILE *arq){
   double *r  = malloc(sizeof(double)*SL->n);
   double *r1 = malloc(sizeof(double)*SL->n);
   double *z  = malloc(sizeof(double)*SL->n);
   double *z1 = malloc(sizeof(double)*SL->n);
   double *p  = malloc(sizeof(double)*SL->n);
   double *p1 = malloc(sizeof(double)*SL->n);
   double *x1 = malloc(sizeof(double)*SL->n);
   
   if(!r || !r1 || !z || !z1 || !p || !p1 || !x1){
      fprintf(stderr, "Erro de alocação!\n");
      exit(ERRALLOC);
   }

   double tempo = timestamp();

   //calcula R0
   somaVetMatxVet(SL, SL->Sim.b, x, -1, r, SL->n);

   //z0 := M^(-1)*r
   multMatVet(M, r, z, SL->n);

   //p0 = z0
   memcpy(p, z, SL->n * sizeof(double));

   for(int iter = 0; iter < SL->i; ++iter){
      //alpha(k) := r(k)T*z(k) / p(k)T*A*p(k)
      double alpha = (multVetVet(r, z, SL->n)) / (multVetMatVet(p, SL, p, SL->n));
      if(isnan(alpha) || isinf(alpha)){
         break;
      }

      //x(k+1) := x(k) + a(k)*p(k)
      somaVetVet(x, alpha, p, x1, SL->n);

      //r(k+1) := r(k) - a(k)*A*p(k)
      somaVetMatxVet(SL, r, p, -alpha, r1, SL->n);

      // x ( max ( |xi - xi-1| / |xi| ) < ε )
      if (normamax (x1, x, SL -> n) < err){
         break;
      }

      //z(k+1) := M^(-1)*r(k+1)
      multMatVet(M, r1, z1, SL->n);

      //beta(k) := r(k+1)T*z(k+1) / r(k)T*z(k)
      double beta = multVetVet(r1, z1, SL->n) / multVetVet(r, z, SL->n);
      if(isnan(beta) || isinf(beta)){
         break;
      }

      //p(k+1) := z(k+1) + beta*p(k)
      somaVetVet(z1, beta, p, p1, SL->n);
      
      //Escreve na saida a normamax da iteração
      fprintf(arq, "# iter %d: %.15g\n", iter+1, normamaxAbs(x1, x, SL->n));

      //r = r1
      memcpy(r, r1, SL->n * sizeof(double));
      //x = x1
      memcpy(x, x1, SL->n * sizeof(double));
      //pk = pk1
      memcpy(p, p1, SL->n * sizeof(double));
      //z = z1
      memcpy(z, z1, SL->n * sizeof(double));
   }

   free(x1);
   free(r);
   free(r1);
   free(z);
   free(z1);
   free(p);
   free(p1);

   //retorna tempo medio por iteração
   return (timestamp()-tempo) / SL->i;
}
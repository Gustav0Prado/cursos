#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "oper.h"
#include "sistema.h"
#include "utils.h"

//calcula norma L2 do residuo
double normaL2(double *r, int n, double *tempR){
   *tempR = timestamp();

   double soma = 0.0;
   for(int i = 0; i < n; ++i){
      soma += r[i]*r[i];
   }

   *tempR = timestamp() - (*tempR);

   return sqrt(soma);
}

//calcula norma maxima entre dois vetores
// max ( |xi - xi-1| / |xi| )
double normamax(double *x, double *x1, int n){
   double max = -1.0;
   double norma;

   for(int i = 0; i < n; ++i){
      norma = fabs(x[i]-x1[i]) / fabs(x[i]);
      max = (norma > max) ? norma : max;
   }

   return max;
}

//Realiza método do gradiente conjugado e retorna o tempo médio levado pelas iterações
//Criterio de parada eh apenas o num de iteracoes
double GradConjIt(SistLinear_t *SL, double *x, double **M){
   double *r  = malloc(sizeof(double)*SL->n);
   double *r1 = malloc(sizeof(double)*SL->n);
   double *z  = malloc(sizeof(double)*SL->n);
   double *z1 = malloc(sizeof(double)*SL->n);
   double *p  = malloc(sizeof(double)*SL->n);
   double *p1 = malloc(sizeof(double)*SL->n);
   double *x1 = malloc(sizeof(double)*SL->n);
   
   double tempo = timestamp();
   int iter;

   //calcula R0
   somaVetMatxVet(SL->A, SL->b, x, -1, r, SL->n);

   //z0 := M^(-1)*r
   multMatVet(M, r, z, SL->n);

   //p0 = z0
   memcpy(p, z, SL->n * sizeof(double));

   for(iter = 0; iter < SL->i; ++iter){
      //alpha(k) := r(k)T*z(k) / p(k)T*A*p(k)
      double alpha = (multVetVet(r, z, SL->n)) / (multVetMatVet(p, SL->A, p, SL->n));

      //x(k+1) := x(k) + a(k)*p(k)
      somaVetVet(x, alpha, p, x1, SL->n);

      //r(k+1) := r(k) - a(k)*A*p(k)
      somaVetMatxVet(SL->A, r, p, -alpha, r1, SL->n);

      //z(k+1) := M^(-1)*r(k+1)
      multMatVet(M, r1, z1, SL->n);

      //beta(k) := r(k+1)T*z(k+1) / r(k)T*z(k)
      double beta = multVetVet(r1, z1, SL->n) / multVetVet(r, z, SL->n);

      //p(k+1) := z(k+1) + beta*p(k)
      somaVetVet(z1, beta, p, p1, SL->n);

      //imprime norma maxima do vetor x
      printf("# iter %4d: %.15g\n", iter+1, normamax(x1, x, SL->n));

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
double GradConjErr(SistLinear_t *SL, double *x, double **M, double err){
   double *r  = malloc(sizeof(double)*SL->n);
   double *r1 = malloc(sizeof(double)*SL->n);
   double *z  = malloc(sizeof(double)*SL->n);
   double *z1 = malloc(sizeof(double)*SL->n);
   double *p  = malloc(sizeof(double)*SL->n);
   double *p1 = malloc(sizeof(double)*SL->n);
   double *x1 = malloc(sizeof(double)*SL->n);
   
   double tempo = timestamp();
   int iter;

   //calcula R0
   somaVetMatxVet(SL->A, SL->b, x, -1, r, SL->n);

   //z0 := M^(-1)*r
   multMatVet(M, r, z, SL->n);

   //p0 = z0
   memcpy(p, z, SL->n * sizeof(double));

   for(iter = 0; iter < SL->i; ++iter){
      //alpha(k) := r(k)T*z(k) / p(k)T*A*p(k)
      double alpha = (multVetVet(r, z, SL->n)) / (multVetMatVet(p, SL->A, p, SL->n));

      //x(k+1) := x(k) + a(k)*p(k)
      somaVetVet(x, alpha, p, x1, SL->n);

      //r(k+1) := r(k) - a(k)*A*p(k)
      somaVetMatxVet(SL->A, r, p, -alpha, r1, SL->n);

      //max ( |xi - xi-1| / |xi| )
      if(normamax(r1, r, SL->n) < err){
         break;
      }

      //z(k+1) := M^(-1)*r(k+1)
      multMatVet(M, r1, z1, SL->n);

      //beta(k) := r(k+1)T*z(k+1) / r(k)T*z(k)
      double beta = multVetVet(r1, z1, SL->n) / multVetVet(r, z, SL->n);

      //p(k+1) := z(k+1) + beta*p(k)
      somaVetVet(z1, beta, p, p1, SL->n);

      //imprime norma maxima do vetor x
      printf("# iter %4d: %.15g\n", iter+1, normamax(x1, x, SL->n));

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
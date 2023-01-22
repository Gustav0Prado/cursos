#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "edo.h"
#include "matriz.h"

#define TAM 3

//funcao aloca edo, imprimir matriz melhor, seidel alternativo dando inf

double p(double x){
   return x+1;
}

double q(double x){
   return -2;
}

double r(double x){
   // (1-x^2)e^-x
   return ( (1-(x*x)) * exp(-x));
}

int main() {
   int n_malha[TAM] = {5, 10, 100};
   
   Edo *edo = malloc(sizeof(Edo));
   edo->a = 0;
   edo->b = 1;
   edo->ya = -1;
   edo->yb = 0;
   edo->p = &p;
   edo->q = &q;
   edo->r = &r;

   for(int i = 0; i < TAM; ++i)
   {
      edo->n = n_malha[i];

      SL_Tridiag *SL = alocaSisLin(edo->n);      
      double *x = malloc(sizeof(double)*SL->n);
      double tTotal;

      memset(x, 0, sizeof(double)*SL->n);

      printf("n: %d\n", edo->n);

      gaussseidelDiag(SL, edo, x, &tTotal);
      imprimeSL(SL);
      printf("Tempo Gauss-Seidel gerando matriz: %g\n", tTotal);
      printf("Vetor Solução: \n");
      imprimeVetor(x, SL->n);
      printf("Norma L2 do resíduo: %g\n", normaL2(SL, x));

      memset(x, 0, sizeof(double)*SL->n);

      gaussseidelFunc(edo, x, &tTotal);
      printf("\nTempo Gauss-Seidel sem gerar matriz: %g\n", tTotal);
      printf("Vetor Solução: \n");
      imprimeVetor(x, SL->n);
      printf("Norma L2 do resíduo: %g\n", normaL2(SL, x));

      printf("----------------------------------------------\n");

      desalocaSisLin(SL);
      free(x);
   }

   free(edo);
}
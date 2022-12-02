#include <stdio.h>
#include <stdlib.h>
#include "edo.h"

#define TAM 3

double p(double x){

}

double q(double x){
   
}

double r(double x){
   
}

int main() {
   int n_malha[TAM] = {5, 10, 100};

   Edo *edo = malloc(sizeof(edo));
   edo->a = 0;
   edo->b = 0;
   edo->ya = -1;
   edo->yb = 0;
   edo->p = p;
   edo->q = q;
   edo->r = r;

   for(int i = 0; i < TAM; ++i)
   {
      double tempo;
      edo->n = n_malha[i];
      //calcula valores da matriz
      //mostra matriz
      //gauss-seidel Diagonal
         //calcula residuo e norma L2
         //mostra norma L2, tempo e solucao
      //gauss-seidel calculando
         //calcula residuo e norma L2
         //mostra norma L2, tempo e solucao
   }
}
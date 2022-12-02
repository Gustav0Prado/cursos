#include "edo.h"

void calculaFunc(SL_Tridiag *SL, Edo *edo, double h){
   double h = (edo->yb - edo->ya) / (edo->n + 1);
   double xi;

   //n comeca em 1????
   for (int i = 0; i < edo->n; ++i){
      xi = (h*i) + edo->a;
      SL->a[i] = 1 - p(xi) * (h/2);
      SL->d[i] = -2 + (h*h) * q(xi);
      SL->c[i] = 1 + p(xi) * (h/2);
      SL->b[i] = h*h * edo->r(xi);
   }
}

/*
   Metodo de Gauss-Seidel usando matrizes diagonais formadas por vetores
*/
void seidelDiag(){

}

/*
   Metodo de Gauss-Seidel usando a funcao para calcular os valores
*/
void seidelFunc(){

}
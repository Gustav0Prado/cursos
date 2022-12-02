#include <math.h>
#include "edo.h"
#include "utils.h"

double normaL2(SL_Tridiag *SL, double *x){
   double *r = malloc(sizeof(double)*SL->n);

   //primeiro passo fora do laco
   r[0] = SL->b[0] - SL->d[0]*x[0] + SL->c[0]*x[1];
   
   //parte interna da matriz
   for(int i = 1; i < SL->n-1; ++i){
      r[i] = SL->b[i] - SL->a[i-1]*x[i-1] + SL->d[i]*x[i] + SL->c[i]*x[i+1];
   }

   //ultimo passo fora do laco
   r[SL->n-1] =  SL->b[SL->n-1] - SL->a[SL->n-2]*x[SL->n-2] + SL->d[SL->n-1]*x[SL->n-1];

   //soma dos quadrados do residuo
   double soma = 0.0;
   for(int i = 0; i < SL->n; ++i){
      soma += r[i]*r[i];
   }

   free(r);
   return sqrt(soma);
}

void calculaDiag(SL_Tridiag *SL, Edo *edo){
   double h = (edo->b - edo->a) / (edo->n + 1);
   double xi;

   //calcula valores baseado na eq generica
   for (int i = 0; i < edo->n; ++i){
      xi = h*(i+1) + edo->a;
      SL->a[i] = 1 - (edo->p(xi) * h)/2.0;
      SL->d[i] = -2 + (h*h) * edo->q(xi);
      SL->c[i] = 1 + edo->p(xi) * (h/2);
      SL->b[i] = h*h * edo->r(xi);
   }

   //ya e yb são conhecidos, "passam" para o outro lado diminuindo
   SL->b[0] -= edo->ya * (1 - (edo->p(xi) * h)/2.0);
   SL->b[SL->n-1] -= edo->yb * (1 + edo->p(xi) * (h/2));
}

/*
   Metodo de Gauss-Seidel usando matrizes diagonais formadas por vetores
*/
void gaussseidelDiag(SL_Tridiag *SL, Edo *edo, double *x, double *tTotal){
   *tTotal = timestamp();

   //Calcula valores da matriz
   calculaDiag(SL, edo);

   //Realiza 50 iterações
   for(int it = 0; it < MAXIT; ++it){
      //primeira linha nao tem a
      x[0] = (SL->b[0] - SL->c[0]*x[1]) / SL->d[0];

      //linhas internas da matriz
      for(int i = 1; i < SL->n-1; ++i){
         // x(i) = b(i) - a*x(i-1) - c*x(i+1) / d(i)
         x[i] = (SL->b[i] - SL->a[i-1]*x[i-1] - SL->c[i]*x[i+1]) / SL->d[i];
      }

      //ultima linha nao tem c
      x[SL->n-1] = (SL->b[SL->n-1] - SL->a[SL->n-2]*x[SL->n-2]) / SL->d[SL->n-1];
   }

   *tTotal = timestamp() - *tTotal;
}

/*
   Metodo de Gauss-Seidel calculando os valores
*/
void gaussseidelFunc(Edo *edo, double *x, double *tTotal){
   *tTotal = timestamp();
   
   //Realiza 50 iterações
   double h = (edo->b - edo->a) / (edo->n + 1);
   //isso aqui ta certo??
   double d = -4*h*h - 4;
   double a = 2-2*h;
   double c = 2+2*h;

   for(int it = 0; it < MAXIT; ++it){
      //primeira linha nao tem a
      x[0] = (2*h*h*edo->r(0) - c*x[1]) / d;

      //linhas internas da matriz
      for(int i = 1; i < edo->n-1; ++i){
         // x(i) = b(i) - a*x(i-1) - c*x(i+1) / d(i)
         x[i] = (2*h*h*edo->r(i) - a*x[i-1] - c*x[i+1]) / d;
      }

      //ultima linha nao tem c
      x[edo->n-1] = (2*h*h*edo->r(edo->n-1) - a*x[edo->n-2]) / d;
   }

   *tTotal = timestamp() - *tTotal;
}
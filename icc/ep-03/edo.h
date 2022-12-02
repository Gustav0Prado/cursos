#ifndef __EDO_H__
#define __EDO_H__

#define MAXIT 50

typedef struct{
   double *d, *a, *c, *b;
   int n;
} SL_Tridiag;

typedef struct{
   double a, b, ya, yb;
   double (*p)(double), (*q)(double), (*r)(double);
   int n;
} Edo;

double normaL2(SL_Tridiag *SL, double *x);

void calculaDiag(SL_Tridiag *SL, Edo *edo);

void gaussseidelDiag(SL_Tridiag *SL, Edo *edo, double *x, double *tTotal);

void gaussseidelFunc(Edo *edo, double *x, double *tTotal);

#endif
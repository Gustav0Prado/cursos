#ifndef __METODOS_H__
#define __METODOS_H__

#include "sistema.h"

double normaL2(double *r, int n, double *tempR);

double normamax(double *x, double *x1, int n);

double GradConjIt(SistLinear_t *SL, double *x, double **M);

double GradConjErr(SistLinear_t *SL, double *x, double **M, double err);

#endif
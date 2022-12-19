#ifndef __METODOS_H__
#define __METODOS_H__

#include "sistema.h"

double GradConjIt(SistLinear_t *SL, double *x, double **M);

double GradConjErr(SistLinear_t *SL, double *x, double **M, double err);

#endif
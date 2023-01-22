#ifndef __MATRIZ_H__
#define __MATRIZ_H__

#include "edo.h"

SL_Tridiag *alocaSisLin(int n);

int desalocaSisLin(SL_Tridiag *SL);

void imprimeSL(SL_Tridiag *SL);

void imprimeVetor(double *x, int n);

#endif
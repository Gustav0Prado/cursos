#ifndef __OPER_H__
#define __OPER_H__

double multVetVet(double *v1, double *v2, int n);

double multVetMatVet(double *v1, double **A, double *v2, int n);

void somaVetVet(double *v1, double m, double *v2, double *res, int n);

void multMatVet(double **A, double *v, double *res, int n);

void somaVetMatxVet(double **A, double *v1, double *v2, double m, double *res, int n);

#endif
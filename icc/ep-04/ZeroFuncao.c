#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

double newtonRaphson (Polinomio p, double x0, double eps,
		   int *it, double *raiz)
{
	double erro;
	do{

	} while(erro > eps && *it < MAXIT);
}


double secante (Polinomio p, double x0, double x1, double eps,
	     int *it, double *raiz)
{
	double erro;
	do{

	} while(erro > eps && *it < MAXIT);
}


void calcPolinomio_rapido(Polinomio p, double x, double *px, double *dpx)
{
	*px = 0;
	*dpx = 0;
	for(int i = p.grau; i > 0; --i){
		*px = (*px)*x + p.p[i];
		*dpx = (*dpx)*x + *px;
	}
	*px = *px*x + p.p[0];
}


void calcPolinomio_lento(Polinomio p, double x, double *px, double *dpx)
{
	for(int i = p.grau; i >= 0; --i){
		*px += p.p[i] * pow(x, i);
		*dpx += i*p.p[i] * pow(x, i-1);
	}
}

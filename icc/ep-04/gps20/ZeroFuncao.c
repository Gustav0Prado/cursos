#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

double newtonRaphson (Polinomio p, double x0, double eps,
		   int *it, double *raiz, double *tempo, void calcPolinomio(Polinomio p, double x, double *px, double *dpx))
{
	double px, dpx, erro, xprox, L;
	double fy = 0;
	double xi = x0;

	*it = 0;
	*tempo = timestamp();

	do{
		calcPolinomio(p, xi, &px, &dpx);
		//calcula L
		if(fabs(dpx) > DBL_EPSILON){
			//salva valor valido de dpx
			L = dpx;
			fy = dpx;
		}
		else{
			//L eh o ultimo valor valido de dpx
			L = fy;
		}

		//calcula x(i+1)
		xprox = xi - (px/L);
		if(L == 0){
			fprintf(stderr, "ERRO: Divisão por 0 - Derivada do polinomio no ponto x0 eh 0\n");
			xi = xprox;
			break;
		}

		//erro absoluto aproximado
		erro = (fabs(xprox - xi));

		//proxima iteracao
		xi = xprox;
		++(*it);
	} while(erro > eps && *it < MAXIT);

	*raiz = xi;
	*tempo = timestamp() - *tempo;

	return erro;
}


double secante (Polinomio p, double x0, double x1, double eps,
	     int *it, double *raiz, double *tempo, void calcPolinomio(Polinomio p, double x, double *px, double *dpx))
{
	double erro, xprox, pxi, pxant, dpx, L;
	double fy = 0;
	double xi = x1;
	double xant = x0;

	*it = 0;
	*tempo = timestamp();

	do{
		//f(xi), f(x(i-1))
		calcPolinomio(p, xi, &pxi, &dpx);
		calcPolinomio(p, xant, &pxant, &dpx);

		//Calcula L
		if(fabs(pxi - pxant) > DBL_EPSILON){
			//Salva valor valido de (pxi - pxant)
			L = (pxi - pxant);
			fy = (pxi - pxant);
		}
		else{
			//L eh o ultimo valor valido de (pxi - pxant)
			L = fy;
		}

		xprox = xi - ( (( pxi * (xi-xant) )) / (pxi - pxant) );
		if(L == 0){
			fprintf(stderr, "ERRO: Divisão por 0 - Valores de f(x) e f(x-1) são iguais/zero\n");
			break;
		}
		//erro absoluto aproximado
		erro = (fabs(xprox - xi));

		//proxima iteracao
		xant = xi;
		xi = xprox;
		++(*it);
	} while(erro > eps && *it < MAXIT);

	*raiz = xi;
	*tempo = timestamp() - *tempo;

	return erro;
}


void calcPolinomio_rapido(Polinomio p, double x, double *px, double *dpx)
{
	double b = 0.0;
	double c = 0.0;
	for(int i = p.grau; i > 0; --i){
		b = b*x + p.p[i];
		c = c*x + b;
	}
	b = b*x + p.p[0];
	*px = b;
	*dpx = c;
}


void calcPolinomio_lento(Polinomio p, double x, double *px, double *dpx)
{
	*px = 0;
	*dpx = 0;

	for(int i = p.grau; i > 0; --i){
		*px += p.p[i] * pow(x, i);
		*dpx += i*p.p[i] * pow(x, i-1);
	}

	*px += p.p[0] * pow(x, 0);
}

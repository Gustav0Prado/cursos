#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

int main ()
{
  Polinomio p;
  double x0, x1, raiz;
  int it = 0;

  printf("Grau do Polinomio: ");
  scanf("%d", &p.grau);
  p.p = malloc(sizeof(double)*p.grau+1);

  printf("Insira os coeficientes do polinomio: ");
  for(int i = p.grau; i >=0 ; --i){
    scanf("%lg", &p.p[i]);
  }

  printf("x0: ");
  scanf("%lg", &x0);

  printf("x1: ");
  scanf("%lg", &x1);

  printf("erro: %g\n", newtonRaphson(p, x0, EPS, &it, &raiz));
  printf("raiz: %g\n", raiz);
  printf("iteracoes: %d\n", it);

  return 0;
}


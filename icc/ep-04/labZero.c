#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

int main ()
{
  Polinomio p;
  double x0, x1;

  printf("Grau do Polinomio: ");
  scanf("%d", &p.grau);
  p.p = malloc(sizeof(double)*p.grau+1);

  for(int i = p.grau; i >=0 ; --i){
    printf("Valor de a%d: ", i);
    scanf("%lg", &p.p[i]);
  }

  printf("x0: ");
  scanf("%lg", &x0);

  printf("x1: ");
  scanf("%lg", &x1);

  return 0;
}


#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

int main ()
{
  Polinomio p;
  double x0, x1, raiz, tempo;
  int it = 0;
  void (*calcPolinomio) (Polinomio p, double x, double *px, double *dpx);

  printf("Grau do Polinomio: ");
  scanf("%d", &p.grau);
  p.p = malloc(sizeof(double)*(p.grau+1));

  printf("Insira os coeficientes do polinomio: ");
  for(int i = p.grau; i >=0 ; --i){
    scanf("%lg", &p.p[i]);
  }

  printf("x0: ");
  scanf("%lg", &x0);

  printf("x1: ");
  scanf("%lg", &x1);

  //usando calcpolinomio_rapido

  calcPolinomio = calcPolinomio_rapido;

  printf("Calculo do polinômio rápido: \n");

  printf("Método de Newton: \n");
  printf("\terro: %g\n", newtonRaphson(p, x0, EPS, &it, &raiz, &tempo, calcPolinomio));
  printf("\traiz: %g\n", raiz);
  printf("\titeracoes: %d\n", it);
  printf("\ttempo: %g\n", tempo);

  printf("\n");

  printf("Método da Secante: \n");
  printf("\terro: %g\n", secante(p, x0, x1, EPS, &it, &raiz, &tempo, calcPolinomio));
  printf("\traiz: %g\n", raiz);
  printf("\titeracoes: %d\n", it);
  printf("\ttempo: %g\n", tempo);


  //usando calcpolinomio_lento
  printf("\n");
  printf("Calculo do polinômio lento: \n");

  calcPolinomio = calcPolinomio_lento;

  printf("Método de Newton: \n");
  printf("\terro: %g\n", newtonRaphson(p, x0, EPS, &it, &raiz, &tempo, calcPolinomio));
  printf("\traiz: %g\n", raiz);
  printf("\titeracoes: %d\n", it);
  printf("\ttempo: %g\n", tempo);

  printf("\n");

  printf("Método da Secante: \n");
  printf("\terro: %g\n", secante(p, x0, x1, EPS, &it, &raiz, &tempo, calcPolinomio));
  printf("\traiz: %g\n", raiz);
  printf("\titeracoes: %d\n", it);
  printf("\ttempo: %g\n", tempo);

  free(p.p);

  return 0;
}


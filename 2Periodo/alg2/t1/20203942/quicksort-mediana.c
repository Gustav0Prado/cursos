#include "particiona.h"
#include "biblioteca.h"

/* -------------------------------------------------------------------------- */
/* devolve a mediana de a, b e c                                              */

static int mediana(int a, int b, int c) {
  if((a >= b && a <= c) || (a <= b && a >= c)){
    return a;
  }
  else if((b >= c && b <= a) || (b <= c && b >= a)){
    return b;
  }
  else
    return c;
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* ordena v[a..b]  usando o algoritmo  "QuickSort com mediana de  3" e
   devolve v                                                                  */

int *quicksort_mediana(int v[], int a, int b) {
  int m, x, y, z, medi;
  if(a >= b){
    return v;
  }

  x = sorteia(a, b);               /*escolhe x,y,z sorteados*/
  y = sorteia(a, b);
  z = sorteia(a, b);
  medi = mediana(v[x], v[y], v[z]);

  if(medi == v[x]){                /*particiona só funciona com o último elemento como pivô*/
    troca(v, x, b);
  }
  else if(medi == v[y]){
    troca(v, y, b);
  }
  else
    troca(v, z, b);

  m = particiona(v, a, b, medi);
  quicksort_mediana(v, a, m-1);
  quicksort_mediana(v, m+1, b);
}
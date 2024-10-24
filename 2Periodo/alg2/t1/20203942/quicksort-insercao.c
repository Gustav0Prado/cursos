#include "insercao.h"
#include "particiona.h"


/* -------------------------------------------------------------------------- */
/* ordena v[a..b] usando o algoritmo QuickSort com inser��o e devolve v       */

int *quicksort_insercao(int v[], int a, int b, unsigned int m) {
  int p;

  if(a >= b){
    return v;
  }
  if(b-a <= m){
    insercao(v, a, b);
    return v;
  }
  p = particiona(v, a, b, v[b]);
  quicksort_insercao(v, a, p-1, m);
  quicksort_insercao(v, p+1, b, m);
}

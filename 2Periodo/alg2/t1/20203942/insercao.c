#include "biblioteca.h"

/*-------------ambas buscas funcionam, mas deixei a sequencial por padrão-------------*/

/*-----------função de busca binaria--------------*/

int BuscaBin(int x, int v[], int a, int b){
   int m;

   if(a > b){
      return a-1;
   }
   m = (a+b)/2;
   if(compara(x, v[m]) == 0){
      return m;
   }
   if(compara(x, v[m]) == -1){
      return BuscaBin(x, v, a, m-1);
   }

   return BuscaBin(x, v, m+1, b);
}

/*------ função de busca sequencial em vetor ordenado----------*/

int BuscaSeq(int x, int v[], int a, int b){

   if(a > b){
      return a - 1;
   }
   if((compara(x, v[b]) != -1)){
      return b;
   }

   return BuscaSeq(x, v, a, b-1);
}

/*-----------função insere em vetor ordenado-----------*/

int *insere(int v[], int a, int b) {
   unsigned int p, i;

   p = BuscaSeq(v[b], v, a, b-1);
   i = b;
   while(i > p+1){
      troca(v, i, i-1);
      i--;
   }

   return v;
}

/* -------------------------------------------------------------------------- */
/* ordena v[a..b] pelo método da inserção e devolve v */

int *insercao(int v[], int a, int b) {

  if(a >= b){
     return v;
  }
  insercao(v, a, b-1);
  insere(v, a, b);

  return v;
}
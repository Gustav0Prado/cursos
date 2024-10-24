#include "libavl.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
   char c;
   int n;
   tNo *raiz = NULL;
   //le até o fim das entradas
   while(c != EOF){
      //le instrucao char + inteiro
      c = getchar();
      scanf("%d", &n);
      //inclusao ou exclusao
      if(c == 'i'){
         raiz = inclui(raiz, n);
      }
      else if(c == 'r'){
         raiz = exclui(raiz, n);
      }
   }

   //imprime em ordem
   emOrdem(raiz);

   //da free em todos os nodos da arvore
   destroiArvore(raiz);
   raiz = NULL;
   return 0;
}
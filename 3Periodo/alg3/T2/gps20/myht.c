#include "libht.h"
#include <stdio.h>

int main(){
   tTabHash T = {0};
   char c;
   int k;

   //le instrução
   c = getchar();
   //enquanto houver dados na stream
   while(c != EOF){
      //le chave
      scanf("%d", &k);
      if(c == 'i'){
         inserir(&T, k);
      }
      else if(c == 'r'){
         remover(&T, k);
      }
      //le proxima instrucao
      c = getchar();
   }
   imprimeT(T);
   destroiTabela(T);

   return 0;
}
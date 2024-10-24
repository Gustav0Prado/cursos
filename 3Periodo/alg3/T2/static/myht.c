#include "libht.h"
#include <stdio.h>
int main(){
   tTabHash T;
   char c;
   int k;

   while(c != EOF){
      c = getchar();
      scanf("%d", &k);
      if(c == 'i'){
         inserir(&T, k);
      }
      else if(c == 'r'){
         remover(&T, k);
      }
   }
   imprimeT(T);
}
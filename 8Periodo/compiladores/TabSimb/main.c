#include "stack.h"
#include <string.h>
#include <stdio.h>

int main(){
   Pilha_t *stack = iniciaPilha();
   char nome[2] = "a";
   char atual = 'a';

   for(int i = 0; i < 5; ++i){
      inserePilha(nome, stack);
      atual++;
      nome[0] = atual;
   }
   printPilha(stack);

   removePilha(3, stack);
   printPilha(stack);

   //Busca de um elemento
   printf("Busca do identificador 'a': %p\n\n", buscaPilha("a", stack));

   //Remove todos os elementos que sobraram na pilha
   removePilha(tamanhoPilha(stack), stack);
   printPilha(stack);

   finalizaPilha(stack);
}
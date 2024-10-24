#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

/*
   Inicia estrutura da Pilha
*/
int iniciaPilha(Pilha_t *pilha){
   if(pilha){
      pilha->topo = 0;
      return 0;
   }

   return -1;
}

/*
   Tenta inserir um identificador na pilha, retorna 0 caso sucesso e -1 caso falhe
*/
int empilha(Pilha_t *pilha, int elem){
   if(pilha){
      if(pilha->topo > TAM_PILHA){
         perror("Erro: Tamanho máximo da pilha");
         return -1;
      }
      else{
         pilha->tipos[pilha->topo] = elem;
         pilha->topo++;
         return 0;
      }
   }
   perror("Erro: Identificador ou pilha Nulos");
   return -1;
}

/*
   Retorna o elemento do topo
*/
int desempilha(Pilha_t *pilha){
   if(pilha){
      pilha->topo--; 
      return pilha->tipos[pilha->topo];
   }
   return -1;
}

/*
   Printa elementos da pilha
*/
void printPilha(Pilha_t *pilha){
   if(pilha){
      printf("----INICIO DA PILHA----\n");
      for(int i = pilha->topo-1; i >= 0; --i){
         printf("%d\n", pilha->tipos[i]);
      }
      printf("----FIM DA PILHA----\n\n");
   }
}

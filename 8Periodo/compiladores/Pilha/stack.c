#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

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
int inserePilha(Pilha_t *pilha, void* elem){
   if(elem && pilha){
      if(pilha->topo > TAM_PILHA){
         perror("Erro: Tamanho máximo da pilha");
         return -1;
      }
      else{
         pilha->elem[pilha->topo] = elem;
         pilha->topo++;
         return 0;
      }
   }
   perror("Erro: Identificador ou pilha Nulos");
   return -1;
}

/*
   Remove últimos n elementos da pilha e retorna 0 em caso de sucesso e -1 em caso de falha
*/
void* desempilha(Pilha_t *pilha){
   if(pilha){
      pilha->topo--; 
      return pilha->elem[pilha->topo];
   }
   return NULL;
}

/*
   Printa elementos da pilha
*/
void printPilha(Pilha_t *pilha){
   if(pilha){
      printf("----INICIO DA PILHA----\n");
      for(int i = 0; i < pilha->topo; ++i){
        int *int_elem = (int *) pilha->elem[pilha->topo-1];
        printf("%d\n", *int_elem);
      }
      printf("----FIM DA PILHA----\n\n");
   }
}

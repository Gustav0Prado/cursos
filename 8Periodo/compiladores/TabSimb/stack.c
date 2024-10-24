#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

/*
   Inicia estrutura da Pilha
*/
Pilha_t *iniciaPilha(){
   Pilha_t *aux = malloc(sizeof(Pilha_t));

   aux->top = NULL;

   return aux;
}

/*
   Tenta inserir um identificador na pilha, retorna 0 caso sucesso e -1 caso falhe
*/
int inserePilha(char *ident, Pilha_t *stack){
   if(ident && stack){
      Var_t *newVar = malloc(sizeof(Var_t));
      
      newVar->ident = malloc(sizeof(ident));
      strncpy(newVar->ident, ident, (int)sizeof(ident));

      newVar->next = stack->top;
      stack->top = newVar;

      return 0;
   }
   perror("Erro: Identificador ou pilha Nulos");
   return -1;
}

/*
   Remove últimos n elementos da pilha e retorna 0 em caso de sucesso e -1 em caso de falha
*/
int removePilha(int n, Pilha_t *stack){
   if(stack){
      if(tamanhoPilha(stack) < n){
         perror("Erro: Tentou remover mais elementos do que a pilha possui");
         return -1;
      }
      Var_t *topo;
      for(int i = 0; i < n; ++i){
         topo = stack->top;

         stack->top = topo->next;

         free(topo->ident);
         topo->next = NULL;
         free(topo);
         topo = NULL;
      }
      return 0;
   }
   return -1;
}

/*
   Retorna atributos da variável buscada
*/
Var_t *buscaPilha(char *ident, Pilha_t *stack){
   if(stack && ident){
      Var_t *aux = stack->top;
      while(aux != NULL){
         if(strcmp(ident, aux->ident) == 0){
            return aux;
         }
         else{
            aux = aux->next;
         }
      }
   }
  return NULL;
}

/*
   Desaloca estruturas da pilha
*/
int finalizaPilha(Pilha_t *stack){
   if(stack){
      if(stack->top != NULL){
         perror("Erro: Tentou finalizar pilha não vazia");
         return -1;
      }
      else{
         free(stack);
         stack = NULL;
      }
   }
   return -1;
}

/*
   Printa elementos da pilha
*/
void printPilha(Pilha_t *stack){
   if(stack){
      printf("----INICIO DA PILHA----\n");
      Var_t *aux = stack->top;
      while(aux != NULL){
         printf("%s\n", aux->ident);
         aux = aux->next;
      }
      printf("----FIM DA PILHA----\n\n");
   }
}

/*
   Retorna tamanho da pilha
*/
int tamanhoPilha(Pilha_t *stack){
   int cont = 0;
   if(stack){
      Var_t *aux = stack->top;
      while(aux != NULL){
         cont++;
         aux = aux->next;
      }
   }

   return cont;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabsimb.h"

/*
   Inicia estrutura da TabSimb
*/
TabSimb_t *iniciaTabSimb(){
   TabSimb_t *aux = malloc(sizeof(TabSimb_t));

   aux->top = NULL;

   return aux;
}

/*
   Tenta inserir um identificador na TabSimb, retorna 0 caso sucesso e -1 caso falhe
*/
int insereTabSimb(char *ident, TabSimb_t *tab){
   if(ident && tab){
      Var_t *newVar = malloc(sizeof(Var_t));
      
      newVar->ident = malloc(sizeof(ident));
      strncpy(newVar->ident, ident, (int)sizeof(ident));

      newVar->next = tab->top;
      tab->top = newVar;

      return 0;
   }
   perror("Erro: Identificador ou TabSimb Nulos");
   return -1;
}

/*
   Remove últimos n elementos da TabSimb e retorna 0 em caso de sucesso e -1 em caso de falha
*/
int removeTabSimb(int n, TabSimb_t *tab){
   if(tab){
      if(tamanhoTabSimb(tab) < n){
         perror("Erro: Tentou remover mais elementos do que a TabSimb possui");
         return -1;
      }
      Var_t *topo;
      for(int i = 0; i < n; ++i){
         topo = tab->top;

         tab->top = topo->next;

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
Var_t *buscaTabSimb(char *ident, TabSimb_t *tab){
   if(tab && ident){
      Var_t *aux = tab->top;
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
   Desaloca estruturas da TabSimb
*/
int finalizaTabSimb(TabSimb_t *tab){
   if(tab){
      if(tab->top != NULL){
         perror("Erro: Tentou finalizar TabSimb não vazia");
         return -1;
      }
      else{
         free(tab);
         tab = NULL;
      }
   }
   return -1;
}

/*
   Printa elementos da TabSimb
*/
void printTabSimb(TabSimb_t *tab){
   if(tab){
      printf("----INICIO DA TabSimb----\n");
      Var_t *aux = tab->top;
      while(aux != NULL){
         printf("%s\n", aux->ident);
         aux = aux->next;
      }
      printf("----FIM DA TabSimb----\n\n");
   }
}

/*
   Retorna tamanho da TabSimb
*/
int tamanhoTabSimb(TabSimb_t *tab){
   int cont = 0;
   if(tab){
      Var_t *aux = tab->top;
      while(aux != NULL){
         cont++;
         aux = aux->next;
      }
   }

   return cont;
}

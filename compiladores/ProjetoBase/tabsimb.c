#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabsimb.h"

/*
   Inicia estrutura da TabSimb
*/
void iniciaTabSimb(TabSimb_t *tab){
   tab->top = NULL;
}

/*
   Tenta inserir um identificador na TabSimb, retorna 0 caso sucesso e -1 caso falhe
*/
int insereTabSimb(char *ident, TabSimb_t *tab, int desloc, int tipo){
   if(ident && tab){
      Simb_t *newVar = malloc(sizeof(Simb_t));
      
      newVar->ident = malloc(sizeof(ident));
      strncpy(newVar->ident, ident, (int)sizeof(ident));

      newVar->next = tab->top;
      tab->top = newVar;

      newVar->uni.vs.deslocamento = desloc;
      newVar->uni.vs.tipo = tipo;

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
      Simb_t *topo;
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
Simb_t *buscaTabSimb(char *ident, TabSimb_t *tab){
   if(tab && ident){
      Simb_t *aux = tab->top;
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
      Simb_t *aux = tab->top;
      while(aux != NULL){
         printf("%s - tipo: %d\n", aux->ident, aux->uni.vs.tipo);
         aux = aux->next;
      }
      printf("----FIM DA TabSimb----\n\n");
   }
}

/*
   Atualiza todos os tipos indefinidos com o tipo passado como parametro
*/
void atualizaTipos(TabSimb_t *tab, int tipo){
   if(tab){
      Simb_t *aux = tab->top;
      while(aux != NULL){
         if(aux->uni.vs.tipo == INDEF){
            aux->uni.vs.tipo = tipo;
         }
         aux = aux->next;
      }
   }
}

/*
   Retorna tamanho da TabSimb
*/
int tamanhoTabSimb(TabSimb_t *tab){
   int cont = 0;
   if(tab){
      Simb_t *aux = tab->top;
      while(aux != NULL){
         cont++;
         aux = aux->next;
      }
   }

   return cont;
}

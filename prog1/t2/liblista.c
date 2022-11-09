#include "liblista.h"
#include <stdlib.h>

/*
 * Cria uma lista vazia e a retorna, se falhar retorna NULL.
*/
lista_t * cria_lista (){
   lista_t *l = malloc(sizeof(lista_t));
   
   if(l != NULL){
      l->ini = NULL;
      l->fim = NULL;
      l->tamanho = 0;

      return l;
   }
   return NULL;
}

/*
 * Remove todos os elementos da lista, libera espaco e retorna NULL.
*/
lista_t * destroi_lista (lista_t *l){
   int elemento;

   while(!lista_vazia(l)){
      retira_inicio_lista(l, &elemento);
   }
   l->ini = NULL;
   l->fim = NULL;
   free(l);
   return NULL;
}

/*
 * Retorna 1 se a lista esta vazia e 0 caso contrario.
*/
int lista_vazia (lista_t *l){
   return (l->tamanho == 0);
}

/*
 * Retorna o tamanho da lista, isto eh, o numero de elementos presentes nela.
*/
int tamanho_lista (lista_t *l){
   return l->tamanho;
}

/*
 * Insere o elemento no inicio da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int insere_inicio_lista (lista_t *l, int elemento){
   nodo_t *n = malloc(sizeof(nodo_t));

   if(n != NULL){
      n->elemento = elemento;
      n->prox = l->ini;
      /*elemento unico na lista - fim == inicio*/
      if(l->tamanho == 0){
         l->fim = n;
      }
      l->ini = n;
      l->tamanho++;

      return 1;
   }
   return 0;
}

/*
 * Insere o elemento no final da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int insere_fim_lista (lista_t *l, int elemento){
   nodo_t *n = malloc(sizeof(nodo_t));
   nodo_t *fim = l->fim;
 
   if(n != NULL){
      /*lista com elementos*/
      if(fim != NULL){
         n->elemento = elemento;
         n->prox = NULL;
         fim->prox = n;
         l->fim = n;
         l->tamanho++;

         return 1;
      }
      /*lista vazia*/
      else{
         n->elemento = elemento;
         n->prox = NULL;
         l->ini = n;
         l->fim = n;
         l->tamanho++;

         return 1;
      }
   }
   return 0;
}

/*
 * Insere o elemento na lista garantindo ordenacao em ordem crescente.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int insere_ordenado_lista (lista_t *l, int elemento){
   nodo_t *n;
   nodo_t *m = l->ini;

   /*caso seja menor que o primeiro ou a lista esteja vazia, insere no inicio*/
   /*nao utiliza o nodo n*/
   if(lista_vazia(l) || m->elemento > elemento){
      return insere_inicio_lista(l, elemento);
   }


   n = malloc(sizeof(nodo_t));
   /*varre a lista ate achar um item maior que elemento*/
   while(m->prox != NULL && (m->prox)->elemento <= elemento){
      m = m->prox;
   }
   n->prox = m->prox;
   n->elemento = elemento;
   m->prox = n;
   l->tamanho++;

   return 1;
}

/*
 * Remove o elemento do inicio da lista e o retorna em 'elemento'.
 * Retorna o elemento.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int retira_inicio_lista (lista_t *l, int *elemento){
   nodo_t *ini = l->ini;
   nodo_t *prox = ini->prox;
      
   if(ini != NULL){
      *elemento = ini->elemento;
      l->ini = prox;
      free(ini);
      ini = NULL;
      l->tamanho--;

      return 1;
   }
   return 0;
}

/*
 * Remove o elemento do final da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int retira_fim_lista (lista_t *l, int *elemento){
   nodo_t *fim = l->fim;
   nodo_t *penult = l->ini;

   if(fim != NULL && penult != NULL){
      /*anda ate o penultimo da lista*/
      while(penult->prox != l->fim){
         penult = penult->prox;
      }
      *elemento = fim->elemento;
      penult->prox = NULL;
      l->fim = penult;
      free(fim);
      fim = NULL;
      l->tamanho--;

      return 1;
   }
   return 0;
}

/*
 * Remove o elemento 'elemento' caso ele exista na lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 * Se o elemento nao for encontrado na lista tambem retorna 0.
*/
int retira_elemento_lista (lista_t *l, int elemento){
   nodo_t *n = l->ini;
   nodo_t *m = n->prox;

   /*percorre toda a lista*/
   while(n->prox != NULL){
      if(m->elemento == elemento){
         n->prox = m->prox;
         free(m);
         m = NULL;
         l->tamanho--;

         return 1;
      }
      n = n->prox;
      m = n->prox;
   }
   return 0;
}

/*
 * Retorna 1 se o elemento existe na lista e 0 caso contrario.
*/
int pertence_lista (lista_t *l, int elemento){
   nodo_t *n = l->ini;

   /*percorre toda a lista*/
   while(n != NULL){
      if(n->elemento == elemento){
         return 1;
      }
      n = n->prox;
   }
   return 0;
}
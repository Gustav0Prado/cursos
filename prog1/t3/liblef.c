#include "libmundo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* 
 * Cria uma LEF vazia 
*/
lef_t * cria_lef (){
   lef_t *l = malloc(sizeof(lef_t));

   if(l != NULL){
      l->Primeiro = NULL;
      return l;
   }
   return NULL;
}

/* 
 * Destroi a LEF, sempre retorna NULL. 
 * Note que nao eh possivel desalocar estruturas dentro de evento->dados se existirem 
*/ 
lef_t * destroi_lef (lef_t *l){
   evento_t *e = obtem_primeiro_lef(l);
   evento_diss_t *ptr_tipo_evt;

   while(e != NULL){
      ptr_tipo_evt = e->dados;
      if(e->tipo == 2){
         ptr_tipo_evt->CJ_RUMOR = destroi_conjunto(ptr_tipo_evt->CJ_RUMOR);
      }
      free(e->dados);
      e->dados = NULL;
      free(e);
      e = obtem_primeiro_lef(l);
   }
   free(l);
   return NULL;
}

/* 
 * Adiciona um evento na primeira posicao da LEF. Uma nova copia
 * da estrutura evento sera feita .
*/ 
int adiciona_inicio_lef (lef_t *l, evento_t *evento){
   evento_t *e_aux = malloc(sizeof(evento_t));
   nodo_lef_t *n = malloc(sizeof(nodo_lef_t));

   if(e_aux != NULL && n != NULL){
      e_aux->tempo = evento->tempo;
      e_aux->tipo = evento->tipo;
      e_aux->dados = malloc(evento->tamanho);
      memcpy(e_aux->dados, evento->dados, evento->tamanho);
      n->evento = e_aux;
      n->prox = l->Primeiro;
      l->Primeiro = n;
      return 1;
   }
   return 0;
}

/* 
 * Adiciona um evento de acordo com o valor evento->tempo na LEF. 
 * Uma nova copia da estrutura evento sera feita 
*/
void adiciona_ordem_lef  (lef_t *l, evento_t *evento){
   evento_t *e_aux;
   nodo_lef_t *n, *m;

   /*lef vazia ou novo evento menor que o primeiro*/
   if(l->Primeiro == NULL || (l->Primeiro)->evento->tempo > evento->tempo){
      adiciona_inicio_lef(l, evento);
   }
   else{
      e_aux = malloc(sizeof(evento_t));
      e_aux->tempo = evento->tempo;
      e_aux->tipo = evento->tipo;
      /*evento de fim nao tem dados*/
      if(evento->tamanho > 0){
         e_aux->dados = malloc(evento->tamanho);
      }
      /*copia dados do original*/
      memcpy(e_aux->dados, evento->dados, evento->tamanho);

      /*cria nodo novo e procura um lugar (nodo/evento que tenha tempo maior) - caso igaul, coloca depois*/
      n = malloc(sizeof(nodo_lef_t));
      m = l->Primeiro;
      while(m->prox != NULL && e_aux->tempo >= (m->prox)->evento->tempo){
         m = m->prox;
      }
      n->prox = m->prox;
      n->evento = e_aux;
      m->prox = n;
   }
}

/* 
 * Retorna o primeiro evento da LEF. A responsabilidade por desalocar
 * a memoria associado eh de quem chama a funcao 
*/
evento_t * obtem_primeiro_lef (lef_t *l){
   nodo_lef_t *n = l->Primeiro;
   evento_t *e;

   if(n != NULL){
      e = n->evento;
      l->Primeiro = n->prox;
      free(n);
      n = NULL;
      return e;
   }
   return NULL;
}
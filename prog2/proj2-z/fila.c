#include "fila.h"
#include <stdlib.h>
#include <stdio.h>

Fila * criaFila (){
   Fila *f = malloc(sizeof(Fila));

   if(f != NULL){
      f->ini = NULL;
      f->fim = NULL;
      f->tamanho = 0;

      return f;
   }
   return NULL;
}

Fila * destroiFila (Fila *f){
   while(!filaVazia(f)){
      desenfilera(f);
   }
   f->fim = NULL;
   f->ini = NULL;
   free(f);
   return NULL;
}

int filaVazia (Fila *f){
   return (f->tamanho == 0);
}

int tamanhoFila (Fila *f){
   return f->tamanho;
}

int enfilera(Fila *f, int elemento){
   NodoFila *n = malloc(sizeof(NodoFila));
   NodoFila *fim = f->fim;

   if(n != NULL){
      if(fim != NULL){
         n->id = elemento;
         n->prox = NULL;
         fim->prox = n;
         f->fim = n;
         f->tamanho++;

         return 1;
      }
      /*fila vazia*/
      else{
         n->id = elemento;
         n->prox = NULL;
         f->ini = n;
         f->fim = n;
         f->tamanho++;

         return 1;
      }
   }
   return 0;
}

int desenfilera(Fila *f){
   NodoFila *ini = f->ini;
   NodoFila *prox;
   int elemento;
      
   if(ini != NULL){
      prox = ini->prox;
      elemento = ini->id;
      f->ini = prox;
      free(ini);
      ini = NULL;
      f->tamanho--;
      /*caso seja o unico elemento, torna a fila vazia*/
      if(f->tamanho == 0){
         f->fim = NULL;
      }

      return elemento;
   }
   return -1;
}

void imprimeFila(Fila *f){
   NodoFila *aux = f->ini;

   if(aux != NULL){
      while(aux != NULL){
         printf("%d ", aux->id);
         aux = aux->prox;
      }
      printf("\n");
   }
}

int primeiroFila(Fila *f){
   return (f->ini->id);
}
#include "lista.h"

/*cria lista vazia*/
listaBloco *iniciaLista(){
   listaBloco *lbl = malloc(sizeof(listaBloco));
	lbl->head = NULL;
	lbl->tail = NULL;

   return lbl;
}


/*adiciona bloco no final da lista*/
int insereLista(Bloco *b, Item *i, listaBloco *l){
   noBloco *nb = malloc(sizeof(noBloco));

   if(nb){
      nb->bloco = b;
      nb->item = i;
      if(b == NULL){
         nb->tipo = ITEM;
      }
      else{
         nb->tipo = BLOCO;
      }
      if(l->head == NULL){
         l->head = nb;
         l->tail = nb;
         nb->prox = NULL;
      }
      else{
         nb->prox = l->head;
         l->head = nb;
      }

      return 0;
   }

   return 1;
}

/*remove um bloco da lista*/
int removeLista(noBloco *del, listaBloco *l){
   noBloco *aux;

   if(l != NULL){
      aux = l->head;

      if(aux == del){
         l->head = del->prox;
      }
      else{
         while(aux->prox != del){
            aux = aux->prox;
         }
         aux->prox = del->prox;
      }
      if(del->tipo == BLOCO){
         al_destroy_bitmap(del->bloco->bmp);
         free(del->bloco);
      }
      else{
         al_destroy_bitmap(del->item->anim1);
         al_destroy_bitmap(del->item->anim2);
         free(del->item);
      }
      free(del);
      del = NULL;
   }

   return (del == NULL);
}

/*remove todos os elementos da lista e retorna se a operacao deu certo*/
int destroiLista(listaBloco *lbl){
   while(lbl->head != NULL){
      removeLista(lbl->head, lbl);
   }
   free(lbl);
   lbl = NULL;
   return (lbl == NULL);
}
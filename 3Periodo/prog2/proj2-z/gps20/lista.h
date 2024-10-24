#include "grafico.h"

#ifndef LIST_H__
#define LIST_H__

typedef struct NoBloco{
   struct NoBloco *prox;
   EItem tipo;
   Bloco *bloco;
   Item *item;
} noBloco;


typedef struct ListaDeBlocos{
   noBloco *head;
   noBloco *tail;
} listaBloco;

/*cria lista vazia*/
listaBloco *iniciaLista();

/*adiciona bloco no final da lista*/
int insereLista(Bloco *b, Item *i, listaBloco *l);

/*remove um bloco da lista*/
int removeLista(noBloco *del, listaBloco *l);

/*remove todos os elementos da lista e retorna se a operacao deu certo*/
int destroiLista(listaBloco *lbl);

#endif
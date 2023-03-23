//GRR20203942 GUSTAVO DO PRADO SILVA

#include "queue.h"
#include <stdio.h>

int queue_size (queue_t *queue){
    int cont = 0;
    queue_t *aux = queue;

    if(queue){
        if(aux->next == aux){
            return 1;
        }
        else{
            while(aux->next != queue){
                cont++;
                aux = aux->next;
            }
        }
    }

    return cont;
}

void queue_print (char *name, queue_t *queue, void print_elem (void*) ){

}

/*
    Insere elementos na fila, mas apenas se ambos existem e o elemento esta isolado
*/
int queue_append (queue_t **queue, queue_t *elem){
    queue_t *fila = *queue;
    printf("%p\n", fila);

    if(elem){
        if(elem->prev == NULL && elem->next == NULL){
            //Caso fila esteja vazia
            if( fila == NULL ){
                elem->next = elem;
                elem->prev = elem;

                *(queue) = elem;
            }
            //Caso já tenha elementos
            else{
                elem->next = fila;
                elem->prev = fila->prev;

                fila->prev = elem;

                elem->prev->next = elem;             
            }
        }

        return 0;
    }

    return -1;
}

int queue_remove (queue_t **queue, queue_t *elem){
    if(queue && elem){

    }

    return -1;
}
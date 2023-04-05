//GRR20203942 GUSTAVO DO PRADO SILVA

#include "queue.h"
#include <stdio.h>

int queue_size (queue_t *queue){
    int cont = 0;
    queue_t *aux = queue;

    if(queue){
        //Fila com 1 elemento
        if(aux->next == aux){
            return 1;
        }
        //Anda pela fila até voltar ao primeiro
        else{
            cont = 1;
            while(aux->next != queue){
                cont++;
                aux = aux->next;
            }
        }
    }

    return cont;
}

void queue_print (char *name, queue_t *queue, void print_elem (void*) ){
    if(queue){
        queue_t *aux = queue->next;

        printf("%s  [", name);
        print_elem(queue);
        
        //Anda pela fila até voltar ao primeiro elemento
        while(aux != queue){
            printf(" ");
            print_elem(aux);
            aux = aux->next;
        }
        printf("]\n");
    }
    //Fila vazia
    else{
        printf("%s  []\n", name);
    }
}

/*
    Insere elementos na fila, mas apenas se ambos existem e o elemento esta isolado
*/
int queue_append (queue_t **queue, queue_t *elem){
    queue_t *fila = *queue;

    if(elem){
        //Certifica que elemento está isolado
        if(elem->prev == NULL && elem->next == NULL){
            //Caso fila esteja vazia
            if( fila == NULL ){
                elem->next = elem;
                elem->prev = elem;

                *(queue) = elem;
            }
            //Caso já tenha elementos
            else{
                fila->prev->next = elem;
                elem->prev = fila->prev;

                elem->next = fila;
                fila->prev = elem;
            }
            
            return 0;
        }
    }
    return -1;
}

/*
    Insere elementos na fila, mas apenas se ambos existem e o elemento esta isolado
*/
int queue_remove (queue_t **queue, queue_t *elem){
    queue_t *fila = *queue;

    int found = 0;

    if(fila && elem){
        //Elemento está em uma fila
        if(elem->prev != NULL && elem->next != NULL){
            //Checa com o primeiro elemento
            if(fila == elem){
                found = 1;
            }
            //Compara com os outros até voltar ao primeiro
            else{
                queue_t *aux = fila->next;
                while(aux != fila){
                    if(aux == elem){
                        found = 1;
                    }
                    aux = aux->next;
                }
            }

            if(found){
                //Remove de uma fila com 1 elemento
                if(fila->next == fila && (elem == fila)){
                    *(queue) = NULL;
                }
                //Mais de um elemento
                else{
                    queue_t *ant = elem->prev;
                    queue_t *pos = elem->next;

                    //Arruma ponteiros
                    ant->next = pos;
                    pos->prev = ant;

                    //Caso seja o "primeiro", fila aponta para o prox
                    if(elem == fila){
                        *(queue) = pos;
                    }
                }

                //Remove da fila
                elem->prev = NULL;
                elem->next = NULL;

                return 0;
            }
        }
    }
    return -1;
}

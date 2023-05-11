/*
Criação de threads POSIX em UNIX.
 
Compilar com gcc -Wall thread-create.c -o thread-create -lpthread
 
Carlos Maziero, DINF/UFPR 2020
*/
 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

typedef struct rv_t{
   int lock;
   sem_t key, arrival;
} rv_t;

rv_t rv;

void rv_init(rv_t *r){
   r->lock = 0;
   sem_init(&(r->arrival), 0, 0);    //Semaforo para aguardar chegada da segunda thread
   sem_init(&(r->key), 0, 1);       //Semaforo para aguardar acessos exclusivo
}

void rv_wait(rv_t *r){
   sem_wait(&(r->key));

   r->lock = !r->lock;

   if(!(r->lock)){
      sem_post(&(r->key));
      sem_post(&(r->arrival));
   }
   else{
      sem_post(&(r->key));
      sem_wait(&(r->arrival));
   }
}

void *A (){
   sleep (1);
   printf("A1\n");

   rv_wait(&rv);

   sleep (1);
   printf("A2\n");

   rv_wait(&rv);

   sleep (1);
   printf("A3\n");
}

void *B (){
   printf("B1 - ");

   rv_wait(&rv);

   printf("B2 - ");

   rv_wait(&rv);
 
   printf("B3 - ");
}
 
int main (int argc, char *argv[]){
   pthread_t thread [2] ;

   rv_init(&rv);

   pthread_create (&thread[0], NULL, A, NULL) ;
   pthread_create (&thread[1], NULL, B, NULL) ;
   pthread_join (thread[0], NULL) ;
   pthread_join (thread[1], NULL) ;

   pthread_exit (NULL) ;
}

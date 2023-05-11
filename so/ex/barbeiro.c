/*
Acesso concorrente a uma variável por muitas threads, solução com semáforo.

Compilar com gcc -Wall simpsons.c -lpthread

Carlos Maziero, DINF/UFPR 2020
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_THREADS 2
#define CADEIRAS 4

sem_t mutex, barbeiroPronto, clientePronto, barbeiro, cliente;
int clientes = 0;

void temCabeloCortado(long id){
   printf("\tCliente %ld está tendo o cabelo cortado\n", id);
   sleep(2);
};

void cortaCabelo(){

};

void *Barbeiro(){
   while(1){
      sem_wait(&cliente);
      sem_post(&barbeiro);

      cortaCabelo();

      sem_wait(&clientePronto);
      sem_post(&barbeiroPronto);
   }

   pthread_exit (NULL) ;
}

void *Cliente(void *id){
   while(1){
      printf("Cliente %ld chegou\n", (long)id);
      sem_wait(&mutex);
      if(clientes == CADEIRAS){
         sem_post(&mutex);
         break;
      }
      clientes++;
      sem_post(&mutex);

      printf("Cliente %ld aguardando o barbeiro\n", (long)id);
      sem_post(&cliente);
      sem_wait(&barbeiro);

      temCabeloCortado((long) id);

      sem_post(&clientePronto);
      printf("Cliente %ld terminou\n", (long)id);
      sem_wait(&barbeiroPronto);

      sem_wait(&mutex);
      clientes--;
      sem_post(&mutex);
   }

   pthread_exit (NULL) ;
}

int main (int argc, char *argv[]){
   pthread_t thread [NUM_THREADS] ;
   pthread_attr_t attr ;
   long i, status ;

   // initialize semaphore
   sem_init (&mutex, 0, 1);
   sem_init (&barbeiro, 0, 0);
   sem_init (&cliente, 0, 0);
   sem_init (&barbeiroPronto, 0, 0);
   sem_init (&clientePronto, 0, 0);

   // define attribute for joinable threads
   pthread_attr_init (&attr) ;
   pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE) ;

   status = pthread_create (&thread[0], &attr, Barbeiro, NULL) ;
   if (status){
      perror ("pthread_create") ;
      exit (1) ;
   }

   for(i = 0; i < NUM_THREADS; ++i){
      status = pthread_create (&thread[i], &attr, Cliente, (void *) i) ;
      if (status){
         perror ("pthread_create") ;
         exit (1) ;
      }
   }

   // wait all threads to finish   
   for (i=0; i<NUM_THREADS; i++)
   {
      status = pthread_join (thread[i], NULL) ;
      if (status)
      {
         perror ("pthread_join") ;
         exit (1) ;
      }
   }


   pthread_attr_destroy (&attr) ;
   pthread_exit (NULL) ;
}


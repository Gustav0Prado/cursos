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

#define NUM_THREADS 6

#define PORCOES 3

sem_t vazio, cheio, mutex;
int cont = PORCOES;

void serve_porcao(long id){
   sem_wait(&mutex);

   if(cont == 0){
      sem_post(&vazio);
      printf("\tPorções acabaram! Chamando cozinheiro\n");
      sem_wait(&cheio);
   }

   printf("\tConvidado %ld pegou uma porção!\n", id);
   cont--;

   sem_post(&mutex);
}

void enche_caldeirao(int N){
   sem_wait(&vazio);
   
   printf("Cozinheiro foi chamado! Reabastecendo caldeirao\n");
   cont = PORCOES;

   sem_post(&cheio);
   
}

void come(long id){
   printf("\t\tConvidado %ld comendo!\n", id);
   sleep( 1 + rand() % 3 );
}

void *Cozinheiro(){
   while(1){
      enche_caldeirao(PORCOES);
   }

   pthread_exit (NULL) ;
}

void *Convidado(void *id){
   while(1){
      serve_porcao((long) id);
      come((long) id);
   }

   pthread_exit (NULL) ;
}

int main (int argc, char *argv[]){
   pthread_t thread [NUM_THREADS] ;
   pthread_attr_t attr ;
   long i, status ;

   // initialize semaphore
   sem_init (&mutex, 0, 1);
   sem_init (&vazio, 0, 0);
   sem_init (&cheio, 0, 0);

   // define attribute for joinable threads
   pthread_attr_init (&attr) ;
   pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE) ;

   status = pthread_create (&thread[0], &attr, Cozinheiro, NULL) ;
   if (status){
      perror ("pthread_create") ;
      exit (1) ;
   }

   for(i = 0; i < NUM_THREADS; ++i){
      status = pthread_create (&thread[i], &attr, Convidado, (void *) i) ;
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


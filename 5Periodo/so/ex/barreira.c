/*
Acesso concorrente a uma variável por muitas threads, solução com semáforo.

Compilar com gcc -Wall simpsons.c -lpthread

Carlos Maziero, DINF/UFPR 2020
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define NUM_THREADS  3

typedef struct barrier{
   int cont, max;
   sem_t lock, wall;
} barrier_t;

barrier_t b;

void barrier_init(barrier_t *b, int num){
   sem_init  (&b->lock, 0, 1);      //Acesso exclusivo a barreira
   sem_init  (&b->wall, 0, 0);      //Muro para as threads esperarem a barreira
   b->cont = 0;
   b->max = num;
}

void barrier_wait(barrier_t *b){
   sem_wait(&(b->lock));
   b->cont++;
   if(b->cont < b->max){
      sem_post(&(b->lock));
      sem_wait(&(b->wall));
   }
   else{
      b->cont = 0;
      for(int i = 0; i < b->max-1; ++i){
         sem_post(&(b->wall));
      }
      sem_post(&(b->lock));
   }
}

void *A(){
   printf("A antes\n");
   barrier_wait(&b);
   printf("A depois\n");

   pthread_exit (NULL) ;
}

void *B(){
   printf("B antes\n");
   barrier_wait(&b);
   printf("B depois\n");

   pthread_exit (NULL) ;
}

void *C(){
   printf("C antes\n");
   barrier_wait(&b);
   printf("C depois\n");

   pthread_exit (NULL) ;
}

int main (int argc, char *argv[]){
   pthread_t thread [NUM_THREADS] ;
   pthread_attr_t attr ;
   long i, status ;

   // define attribute for joinable threads
   pthread_attr_init (&attr) ;
   pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE) ;

   //Inicializa barreira
   barrier_init(&b, NUM_THREADS);

   status = pthread_create (&thread[0], &attr, A, NULL) ;
   if (status){
      perror ("pthread_create") ;
      exit (1) ;
   }

   status = pthread_create (&thread[1], &attr, B, NULL) ;
   if (status){
      perror ("pthread_create") ;
      exit (1) ;
   }

   status = pthread_create (&thread[2], &attr, C, NULL) ;
   if (status){
      perror ("pthread_create") ;
      exit (1) ;
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


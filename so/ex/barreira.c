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
   sem_t s;
   int n;
} barrier_t;

barrier_t b;
sem_t c;
int count;

void barrier_init(barrier_t *b, int num){
   sem_init  (&b->s, 0, 0) ;
   sem_init  (&c, 0, 1) ;
   b->n = num;
   count = 0;
}

void barrier_wait(barrier_t *b){
   // initialize semaphore to num
   sem_wait(&c);
   count++;
   //printf("%d  --  %d\n", count, b->n);
   if(count < b->n){
      sem_post(&c);
      sem_wait(&b->s);
      sem_post(&b->s);
   }
   else{
      sem_post(&b->s);
      count = 0;
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


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

sem_t s, b, l, m ;

void *Bart(){
   //while(1){
   for(int i = 0; i < 10; ++i){
      sem_wait (&b) ;
      printf("Bart\n");
      sem_post (&l) ;
   }

   pthread_exit (NULL) ;
}

void *Lisa(){
   for(int i = 0; i < 10; ++i){
      //Espera Lisa
      sem_wait (&l) ;
      printf("\tLisa\n");
      //Libera Maggie
      sem_post (&m) ;
      
      //Espera Segundo Lisa
      sem_wait(&l);
      printf("\tLisa\n");
      //Libera Bart de novo
      sem_post(&b);
   }

   pthread_exit (NULL) ;
}

void *Maggie(){
   for(int i = 0; i < 10; ++i){
      // Espera semaforo da Maggie
      sem_wait (&m) ;
      printf("\t\tMaggie\n");
      //Libera Lisa
      sem_post(&l);
   }

   pthread_exit (NULL) ;
}

int main (int argc, char *argv[]){
   pthread_t thread [NUM_THREADS] ;
   pthread_attr_t attr ;
   long i, status ;

   // initialize semaphore to 1
   sem_init (&s, 0, 1) ;
   sem_init (&b, 0, 1) ;
   sem_init (&l, 0, 0) ;
   sem_init (&m, 0, 0) ;

   // define attribute for joinable threads
   pthread_attr_init (&attr) ;
   pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE) ;

   status = pthread_create (&thread[0], &attr, Bart, NULL) ;
   if (status){
      perror ("pthread_create") ;
      exit (1) ;
   }

   status = pthread_create (&thread[2], &attr, Lisa, NULL) ;
   if (status){
      perror ("pthread_create") ;
      exit (1) ;
   }

   status = pthread_create (&thread[1], &attr, Maggie, NULL) ;
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


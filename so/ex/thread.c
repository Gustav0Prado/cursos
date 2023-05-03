/*
Criação de threads POSIX em UNIX.
 
Compilar com gcc -Wall thread-create.c -o thread-create -lpthread
 
Carlos Maziero, DINF/UFPR 2020
*/
 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int y = 0;

void *threadBody (void *id)
{
  int x = 0;

  sleep (10) ;   
  printf ("x:%d, y:%d\n", ++x, ++y) ;  
  pthread_exit (NULL) ;
}
 
int main (int argc, char *argv[])
{
   pthread_t thread [3] ;
   
   pthread_create (&thread[0], NULL, threadBody, (void *) 0) ;
   pthread_create (&thread[1], NULL, threadBody, (void *) 0) ;
   sleep(1);
   pthread_join (thread[0], NULL) ;
   pthread_join (thread[1], NULL) ;
   sleep(1);
   pthread_create (&thread[2], NULL, threadBody, (void *) 0) ;
   pthread_join (thread[2], NULL) ;
   
   pthread_exit (NULL) ;
}

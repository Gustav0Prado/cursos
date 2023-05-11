/*
Criação de threads POSIX em UNIX.
 
Compilar com gcc -Wall thread-create.c -o thread-create -lpthread
 
Carlos Maziero, DINF/UFPR 2020
*/
#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>   //cpu_set_t , CPU_SET

int y = 0;

void *threadBody (void *id)
{
  /* THREADS 1:1
  cpu_set_t cpuset; 
  int cpu = (long) id;
  CPU_ZERO(&cpuset);
  CPU_SET( cpu , &cpuset);

  sched_setaffinity(0, sizeof(cpuset), &cpuset);*/

  int x = 0;

  sleep (20) ;   
  printf ("x:%d, y:%d\n", ++x, ++y) ;  
  pthread_exit (NULL) ;
}
 
int main (int argc, char *argv[])
{
   pthread_t thread [3] ;
   
   pthread_create (&thread[0], NULL, threadBody, (void *) 0) ;
   pthread_create (&thread[1], NULL, threadBody, (void *) 1) ;
   sleep(1);
   pthread_join (thread[0], NULL) ;
   pthread_join (thread[1], NULL) ;
   sleep(1);
   pthread_create (&thread[2], NULL, threadBody, (void *) 0) ;
   pthread_join (thread[2], NULL) ;
   
   pthread_exit (NULL) ;
}

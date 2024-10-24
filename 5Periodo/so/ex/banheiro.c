/*
Acesso concorrente a uma variável por muitas threads, solução com semáforo.

Compilar com gcc -Wall simpsons.c -lpthread

Carlos Maziero, DINF/UFPR 2020
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS  4
#define LIM 10

#define H 0
#define M 1

typedef struct Lightswitch{
   sem_t mutex;
   int counter;
} ls_t;

sem_t vagas_H, vagas_M, vazio;
ls_t switchH, switchM;

void ls_lock(ls_t *ls, sem_t *sem){
   sem_wait(&ls->mutex);
   ls->counter++;
   //Se for o(a) primeiro(a) a entrar, liga o switch
   if (ls->counter == 1)
   {
      sem_wait(sem);
   }
   sem_post(&ls->mutex);
}

void ls_unlock(ls_t *ls, sem_t* sem){
   sem_wait(&ls->mutex);
   ls->counter--;
   //Se for o ultimo(a) a sair, desliga o switch
   if (ls->counter == 0)
   {
      printf("Banheiro Livre!!\n");
      sem_post(sem);
   }
   sem_post(&ls->mutex);
}


int tempo(){
   //return (1 + rand() % 3);
   return (0.5);
}

void trabalhar(long i, int hm){
   if(hm == H){
      printf("\tHomem  %ld começa a trabalhar\n", i);
      sleep( tempo() );
   }
   else{
      printf("\tMulher %ld começa a trabalhar\n", i);
      sleep( tempo() );
   }
}

void usar_banheiro_h(long i){
   printf("\tHomem  %ld quer entrar no banheiro\n", i);
   //Tenta entrar no banheiro e caso seja o primeiro e o banheiro esteja vazio, liga o switch
   ls_lock(&switchH, &vazio);

   //Entrou no banheiro, tenta entrar em uma porta
   sem_wait(&vagas_H);
   printf("\t\tHomem  %ld entrou no banheiro\n", i);
   sleep(tempo());

   //Sai da porta
   sem_post(&vagas_H);
   printf("\t\tHomem  %ld saiu do banheiro\n", i);

   //Sai do banheiro e caso seja o ultimo, desliga o switch
   ls_unlock(&switchH, &vazio);
}

void usar_banheiro_m(long i){
   printf("\tMulher  %ld quer entrar no banheiro\n", i);
   //Tenta entrar no banheiro e caso seja a primeira e o banheiro esteja vazio, liga o switch
   ls_lock(&switchM, &vazio);

   //Entrou no banheiro, tenta entrar em uma porta
   sem_wait(&vagas_M);
   printf("\t\tMulher  %ld entrou no banheiro\n", i);
   sleep(tempo());

   //Sai da porta
   sem_post(&vagas_M);
   printf("\t\tMulher  %ld saiu do banheiro\n", i);
   
   //Sai do banheiro e caso seja o ultimo, desliga o switch
   ls_unlock(&switchM, &vazio);
}

void *Homem(void *id){
   for(int i = 0; i < LIM; ++i){
      trabalhar((long) id, 0);
      usar_banheiro_h((long) id);
   }

   pthread_exit (NULL) ;
}

void *Mulher(void *id){
   for(int i = 0; i < LIM; ++i){
      trabalhar((long) id, 1);
      usar_banheiro_m((long) id);
   }

   pthread_exit (NULL) ;
}

int main (int argc, char *argv[]){
   pthread_t thread [NUM_THREADS] ;
   pthread_attr_t attr ;
   long i, status ;

   // initialize semaphore
   sem_init (&vagas_H, 0, 3) ;
   sem_init (&vagas_M, 0, 3) ;
   sem_init (&vazio, 0, 1) ;

   sem_init(&(switchH.mutex), 0, 1);
   switchH.counter = 0;

   sem_init(&(switchM.mutex), 0, 1);
   switchM.counter = 0;

   // define attribute for joinable threads
   pthread_attr_init (&attr) ;
   pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE) ;

   for(i = 0; i < NUM_THREADS; ++i){
      status = pthread_create (&thread[i], &attr, Homem, (void *) i) ;
      if (status){
         perror ("pthread_create") ;
         exit (1) ;
      }

      status = pthread_create (&thread[i+2], &attr, Mulher, (void *) i) ;
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


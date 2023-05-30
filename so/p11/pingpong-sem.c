// Problema dos produtores e consumidores

#include <stdio.h>
#include <stdlib.h>
#include "ppos.h"

#define NUMTASKS  1
#define TAMBUFFER 5

task_t task[NUMTASKS] ;
semaphore_t  s_vaga, s_buffer, s_item ;
//Buffer com 16 vagas
int buffer[TAMBUFFER];

// corpo das tarefas
void producerBody(void *id)
{
   while (1){
      task_sleep(1000);
      int item = random() % 99;

      sem_down(&s_vaga);

      sem_down(&s_buffer);
      //insere item no buffer
      printf("p%d produziu %d\n", (int)id, item);
      sem_up(&s_buffer);

      sem_up(&s_item);
   }

   task_exit (0) ;
}

// corpo das tarefas
void consumerBody(void *id)
{
   int item;
   while (1){
      sem_down(&s_item);

      sem_down(&s_buffer);
      //retira item do buffer
      printf("c%d consumiu %d\n", (int)id, item);
      sem_up(&s_buffer);

      sem_up(&s_vaga);

      //print item
      task_sleep (1000);
   }

   task_exit (0) ;
}

int main (int argc, char *argv[]){
   int i ;

   printf ("main: inicio\n") ;

   ppos_init () ;

   // inicia semáforos em 0 (bloqueados)
   sem_init (&s_item,    0) ;
   sem_init (&s_buffer,  1) ;
   sem_init (&s_vaga,    TAMBUFFER) ;

   printf ("%d Produtores e  %d Consumidores...\n",NUMTASKS, NUMTASKS);

   // inicia as tarefas
   for (i=0; i<NUMTASKS; i++){
      task_init (&task[i], producerBody, i) ;
      task_init (&task[i], consumerBody, i) ;
   }

   // aguarda as tarefas encerrarem
   for (i=0; i<NUMTASKS; i++)
      task_wait (&task[i]) ;

   // destroi o semáforo
   sem_destroy (&s_item) ;
   sem_destroy (&s_buffer) ;
   sem_destroy (&s_vaga) ;

   task_exit (0) ;
}
// Problema dos produtores e consumidores

#include <stdio.h>
#include <stdlib.h>
#include "ppos.h"

#define PROD  3
#define CONS  2
#define TAMBUFFER 5

task_t task[PROD+CONS] ;
semaphore_t  s_vaga, s_buffer, s_item ;
//Buffer com 16 vagas
int buffer[TAMBUFFER] = {0};
int head = 0;
int tail = 0;
int qtd = 0;


/*
   Insere um item no buffer
*/
void insertBuffer(int item){
   if(qtd < 5){
      buffer[head] = item;
      head = (head + 1) % TAMBUFFER;
      qtd++;
   }
   else{
      printf("Erro: Buffer cheio\n");
   }
}

/*
   Consome um item do buffer
*/
int consomeBuffer(){
   if(qtd > 0){
      int item = buffer[tail];
      tail = (tail + 1) % TAMBUFFER;
      qtd--;
      return item;
   }
   else{
      printf("Erro: Buffer vazio\n");
      return -1;
   }
}

// corpo das tarefas
void producerBody(void *id)
{
   while (1){
      task_sleep(1000);
      int item = random() % 99;

      sem_down(&s_vaga);

      sem_down(&s_buffer);
      insertBuffer(item);
      printf("p%ld produziu %d\n", (long)id, item);
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
      item = consomeBuffer();
      sem_up(&s_buffer);

      sem_up(&s_vaga);

      printf("\t\tc%ld consumiu %d\n", (long)id, item);
      task_sleep (1000);
   }

   task_exit (0) ;
}

int main (int argc, char *argv[]){
   long i ;

   printf ("main: inicio\n") ;

   ppos_init () ;

   // inicia semáforos em 0 (bloqueados)
   sem_init (&s_item,    0) ;
   sem_init (&s_buffer,  1) ;
   sem_init (&s_vaga,    TAMBUFFER) ;

   printf ("%d Produtores e  %d Consumidores...\n", PROD, CONS);

   // inicia as tarefas
   for (i=0; i<PROD; i++){
      task_init (&task[i], producerBody, (void *)i) ;
   }

   // inicia as tarefas
   for (i=PROD; i<PROD+CONS; i++){
      task_init (&task[i], consumerBody, (void *)i-PROD) ;
   }

   // aguarda as tarefas encerrarem
   for (i=0; i<PROD+CONS; i++)
      task_wait (&task[i]) ;

   // destroi o semáforo
   sem_destroy (&s_item) ;
   sem_destroy (&s_buffer) ;
   sem_destroy (&s_vaga) ;

   task_exit (0) ;
}
#include <stdio.h>
#include <stdlib.h>
#include "ppos_data.h"
#include "ppos.h"
#include "queue.h"

#define STACKSIZE 64*1024	/* tamanho de pilha das threads */

//Tasks e ponteiros para controle
task_t *curr_task;
task_t main_task;
task_t dispatcher_task;

//Fila de prontos
queue_t *readyTasks;

//Ints para controle
int curr_id = 0;
int user_tasks = 0;

//------------------------//------------------------//------------------------//------------------------//------------------------//

//Escalonador do PPOS
task_t *scheduler(){
  int age = -1;

  task_t *first = (task_t *)readyTasks;
  task_t *aux = first->next;
  task_t *min = first;

  // Escolhe task com prioridade mais negativa (menor)
  while( aux != first ){
    if( aux->prio_d < min->prio_d ){
      min = aux;
    }
    aux = aux->next;
  }

  // Envelhece outras tasks
  aux = first;
  do{
    if( aux != min ){
      aux->prio_d += age;
    }
    aux = aux->next;
  } while( aux != first );

  return min;
}

//Funcao para printar elementos da fila, no caso os ids das tasks
void print_elem( void* a ){
  if(a){
    task_t *t = (task_t *)a;
    printf("%d(%d)", t->id, t->prio_d);
  }
}

//Funcao do dispatcher
void dispatcher(){
  while( user_tasks > 0 ){
    #ifdef DEBUG
    printf(MAG);
    queue_print("PPOS: dispatcher   -  Task(s) Queued: ", (queue_t *)readyTasks, print_elem);
    printf(RESET);
    #endif

    task_t *prox = scheduler();

    if(prox != NULL){
      task_switch(prox);

      switch (prox->status)
      {
      case READY:
        //Gira a fila e reseta prioridade dinamica
        //readyTasks = readyTasks->next;
        prox->prio_d = prox->prio_s;
        break;

      case RUNNING:
        break;

      case SUSPENDED:
        break;

      //Tarefa terminada, libera pilha do contexto e remove da fila
      case TERMINATED:
        free(prox->context.uc_stack.ss_sp);
        queue_remove((queue_t **)&readyTasks, (queue_t*)prox);
        user_tasks--;
        break;
      }
    }
  }
  #ifdef DEBUG
  printf (BLU "PPOS: dispatcher   -  Empty task queue!\n" RESET) ;
  #endif
  task_exit(0);
}


// Cria task main e coloca na fila
void createMainTask(){
  //Salva contexto atual na main
  main_task.id = curr_id;
  getcontext(&(main_task).context);
  main_task.status = READY;

  // Adiciona na fila de prontos
  user_tasks++;
  curr_id++;

  queue_append((queue_t **)&readyTasks, (queue_t*)&main_task);
}


// Inicia o sistema do PPPOS
void ppos_init(){
  /* desativa o buffer da saida padrao (stdout), usado pela função printf */
  setvbuf (stdout, 0, _IONBF, 0);

  createMainTask();
  curr_task = &main_task;

  //Inicia dispatcher, mas o remove da fila
  task_init(&dispatcher_task, &dispatcher, NULL);
  queue_remove((queue_t **)&readyTasks, (queue_t*)&dispatcher_task);
  user_tasks--;
}


// Inicializa uma nova tarefa. Retorna um ID> 0 ou erro.
int task_init (task_t *task,			// descritor da nova tarefa
               void  (*start_func)(void *),	// funcao corpo da tarefa
               void   *arg)		// argumentos para a tarefa
{
  void* stack = malloc(STACKSIZE);

  getcontext(&(task->context));

  if(stack){
    //Inicializa stack própria da tarefa
    task->context.uc_stack.ss_sp = stack;
    task->context.uc_stack.ss_size = STACKSIZE;
    task->context.uc_stack.ss_flags = 0;
    task->context.uc_link = 0;

    task->id = curr_id;
    task->status = READY;
    task->prio_d = 0;
    task->prio_s = 0;

    #ifdef DEBUG
    printf (YEL "PPOS: task_init    -  Starting task %d\n" RESET, task->id ) ;
    #endif

    curr_id++;
  }
  else{
    perror ("Erro ao alocar a pilha: ") ;
    return -1;
  }

  makecontext(&(task->context), (void*)(*start_func), 1, arg);

  queue_append((queue_t **)&readyTasks, (queue_t*)task);
  user_tasks++;

  return task->id;
}

// retorna o identificador da tarefa corrente (main deve ser 0)
int task_id(){
  return (curr_task->id);
}

// Termina a tarefa corrente com um valor de status de encerramento
void task_exit(int exit_code){
  curr_task->status = TERMINATED;
  #ifdef DEBUG
  printf (YEL "PPOS: task_exit    -  Exiting task %d\n" RESET, curr_task->id);
  #endif
  
  task_switch(&dispatcher_task);
}

// alterna a execução para a tarefa indicada
int task_switch(task_t *task){
  if(task){
    //Salva task atual em old e nova task como atual
    task_t *aux_task = curr_task;
    curr_task = task;

    #ifdef DEBUG
    printf (YEL "PPOS: task_switch  -  Switching task %d -> %d\n" RESET, aux_task->id, task->id);
    #endif

    return (swapcontext(&(aux_task->context), &(task->context)));
  }

  return -1;
}

// Larga a CPU e volta ao dispatcher
void task_yield(){
  #ifdef DEBUG
  printf (YEL "PPOS: task_yield   -  Task %d yielded the CPU\n" RESET, curr_task->id);
  #endif

  //Tarefa larga a CPU e chama o dispatcher
  task_switch(&dispatcher_task);
}

// Seta a prioridade de uma task, se task for NULL usa a atual (curr_task)
void task_setprio (task_t *task, int prio){
  if(task){
    task->prio_s = prio;
    task->prio_d = prio;
  }
  else{
    curr_task->prio_s = prio;
    curr_task->prio_d = prio;
  }
}

// Retorna a prioridade de uma task, se task for NULL usa a atual (curr_task)
int task_getprio (task_t *task){
  if(task){
    return (task->prio_s);
  }
  else{
    return curr_task->prio_s;
  }
}
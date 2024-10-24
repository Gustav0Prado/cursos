#include <stdio.h>
#include <stdlib.h>
#include "ppos_data.h"
#include "ppos.h"

#define STACKSIZE 64*1024	/* tamanho de pilha das threads */

#define PRONTA   0
#define RODANDO  1
#define SUSPENSA 2
#define TERMINADA 3

task_t *curr_task;
task_t *old_task;
task_t main_task;
int curr_id = 1;

void ppos_init(){
  /* desativa o buffer da saida padrao (stdout), usado pela função printf */
  setvbuf (stdout, 0, _IONBF, 0);
  
  main_task.id = 0;
  curr_task = &main_task;
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
    task->status = PRONTA;

    #ifdef DEBUG
    printf ("task_init: iniciada tarefa %d\n", task->id) ;
    #endif

    curr_id++;
  }
  else{
    perror ("Erro ao alocar a pilha: ") ;
    return -1;
  }

  makecontext(&(task->context), (void*)(*start_func), 1, arg);

  return task->id;
}

// retorna o identificador da tarefa corrente (main deve ser 0)
int task_id(){
  return (curr_task->id);
}

// Termina a tarefa corrente com um valor de status de encerramento
void task_exit(int exit_code){
  curr_task->status = TERMINADA;
  task_switch(&main_task);

  #ifdef DEBUG
  printf ("task_exit: tarefa %d sendo encerrada\n", curr_task->id);
  #endif
}

// alterna a execução para a tarefa indicada
int task_switch(task_t *task){
  if(task){
    //Salva task atual em old e nova task como atual
    old_task = curr_task;
    curr_task = task;

    #ifdef DEBUG
    printf ("task_switch: trocando contexto %d -> %d\n", old_task->id, task->id);
    #endif

    return swapcontext(&(old_task->context), &(curr_task->context));
  }

  return -1;
}

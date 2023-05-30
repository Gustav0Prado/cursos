#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include "ppos_data.h"
#include "ppos.h"
#include "queue.h"

// Tamanho de pilha das threads
#define STACKSIZE 64*1024

//Tasks e ponteiros para controle
task_t *curr_task;
task_t main_task;
task_t dispatcher_task;

//Fila de prontos
queue_t *readyTasks;
queue_t *sleepingTaks;

//Ints para controle
int curr_id = 0;
int user_tasks = 0;

// Estruturas para os alarmes dos "ticks do relogio"
struct sigaction action ;
struct itimerval timer;

unsigned int sysClock;

//------------------------//------------------------//------------------------//------------------------//------------------------//

/*
  Diminui contador de tempo de uma tarefa caso ela seja de usuario
  Caso tempo tenha acabado, retorna ao dispatcher
*/
void timer_tick(){
  curr_task->cpuTime++;
  sysClock++;

  if(curr_task->task_type == USER && --curr_task->quantum == 0){
    task_yield();
  }
}

void timer_start(){
  // registra a ação para o sinal de timer SIGALRM (sinal do timer)
  action.sa_handler = timer_tick;
  sigemptyset (&action.sa_mask);
  action.sa_flags = 0 ;
  if (sigaction (SIGALRM, &action, 0) < 0)
  {
    perror ("Erro em sigaction: ") ;
    exit (1) ;
  }

  // ajusta valores do temporizador para disparar a cada 1 milissegundo
  timer.it_value.tv_usec = 1000;
  timer.it_value.tv_sec  = 0;
  timer.it_interval.tv_usec = 1000;
  timer.it_interval.tv_sec  = 0;

  // arma o temporizador ITIMER_REAL
  if (setitimer (ITIMER_REAL, &timer, 0) < 0)
  {
    perror ("Erro em setitimer: ") ;
    exit (1) ;
  }
}


/*
  Seta a prioridade de uma task, se task for NULL usa a atual (curr_task)
  Task precisa estar entre -20 e 20
*/
void task_setprio (task_t *task, int prio){
  if(task){
    if(prio >= -20 && prio <= 20){
      task->prio_s = prio;
      task->prio_d = prio;
    }
  }
  else{
    if(prio >= -20 && prio <= 20){
      curr_task->prio_s = prio;
      curr_task->prio_d = prio;
    }
  }
}


/*
  Retorna a prioridade de uma task, se task for NULL usa a atual (curr_task)
*/
int task_getprio (task_t *task){
  if(task){
    return (task->prio_s);
  }
  else{
    return curr_task->prio_s;
  }
}


/*
  Escalonador do PPOS
*/
task_t *scheduler(){
  int age = -1;

  task_t *first = (task_t *)readyTasks;
  if(first != NULL){
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

  return NULL;
}


/*
  Funcao para printar elementos da fila, no caso os ids das tasks
*/
void print_elem( void* a ){
  if(a){
    task_t *t = (task_t *)a;
    printf("%d(%d)", t->id, t->prio_d);
  }
}

void print_sleep( void* a ){
  if(a){
    task_t *t = (task_t *)a;
    printf("%d(%d)", t->id, t->wakeTime);
  }
}


/*
  Funcao do dispatcher
*/
void dispatcher(){
  while( user_tasks > 0 ){
    #ifdef DEBUG
    printf(MAG);
    if(readyTasks != NULL) queue_print("PPOS: dispatcher   -  Task(s) Queued: ", (queue_t *)readyTasks, print_elem);
    printf(RESET);
    #endif

    // Checa se há alguma tarefa dormindo que pode ser acordada
    if(sleepingTaks != NULL){
      int time = systime();
      task_t *aux = (task_t *)sleepingTaks;
      task_t *prox;

      // Acorda tarefas que tem limite nesse instante ou anterior
      do{
        prox = aux->next;
        if( aux->wakeTime == time ){
          #ifdef DEBUG
          printf (BLU "PPOS: dispatcher   -  Waking up task %d on %dms\n" RESET, aux->id, systime()) ;
          #endif

          //if( sleepingTaks != NULL )queue_print("Dormindo: ", sleepingTaks, print_sleep);

          task_resume(aux, (task_t **)&sleepingTaks);
        }
        aux = prox;
      } while(aux != (task_t *)sleepingTaks && sleepingTaks != NULL);
    }

    task_t *prox = scheduler();

    if(prox != NULL){
      prox->quantum = DEFQUANTUM;
      task_switch(prox);

      switch (prox->status){
      case READY:
        prox->prio_d = prox->prio_s;
        break;

      case SUSPENDED:
        break;

      //Tarefa terminada, libera pilha do contexto e remove da fila
      case TERMINATED:
        #ifdef DEBUG
        printf (RED "PPOS: dispatcher   -  %d terminated, removing!\n" RESET, prox->id) ;
        #endif
        free(prox->context.uc_stack.ss_sp);
        
        break;
      }
    }
    //Coloca dispatcher pra dormir pra economizar cpu
    else{

    }
  }
  #ifdef DEBUG
  printf (BLU "PPOS: dispatcher   -  Empty task queue!\n" RESET) ;
  #endif
  task_exit(0);
}


/*
  Cria task main e coloca na fila
*/
void createMainTask(){
  //Salva contexto atual na main
  main_task.id = curr_id;
  getcontext(&(main_task).context);
  main_task.status = READY;
  main_task.quantum = DEFQUANTUM;
  main_task.task_type = USER;

  main_task.activations = 1;
  main_task.cpuTime = 0;

  // Adiciona na fila de prontos
  user_tasks++;
  curr_id++;

  queue_append((queue_t **)&readyTasks, (queue_t*)&main_task);
}


/*
  Inicia o sistema do PPOS
*/
void ppos_init(){
  /* desativa o buffer da saida padrao (stdout), usado pela função printf */
  setvbuf (stdout, 0, _IONBF, 0);

  createMainTask();
  curr_task = &main_task;

  //Inicia dispatcher, mas o remove da fila
  task_init(&dispatcher_task, &dispatcher, NULL);
  queue_remove((queue_t **)&readyTasks, (queue_t*)&dispatcher_task);
  user_tasks--;
  dispatcher_task.task_type = SYSTEM;

  sysClock = 0;
  timer_start();
}


/*
  Inicializa uma nova tarefa. Retorna um ID> 0 ou erro.
*/
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

    //Tarefas comecam como de usuário
    task->task_type = USER;

    //Seta valores iniciais de ativação e tempo de cpu
    task->activations = 0;
    task->cpuTime = 0;
    task->creationTime = systime();

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


/*
  Retorna o identificador da tarefa corrente (main deve ser 0)
*/
int task_id(){
  return (curr_task->id);
}

/*
  Termina a tarefa corrente com um valor de status de encerramento
*/
void task_exit(int exit_code){
  curr_task->status = TERMINATED;
  curr_task->exit_code = exit_code;

  //Printa tempo e ativacoes
  printf("Task %d exit: execution time %d ms,", curr_task->id, systime()-curr_task->creationTime);
  printf(" processor time %5d ms, %d activations\n", curr_task->cpuTime, curr_task->activations);

  if(user_tasks == 0){
    //Remove task do dispatcher
    free(dispatcher_task.context.uc_stack.ss_sp);

    #ifdef DEBUG
    printf (RED "PPOS: task_exit    -  Exiting PPOS\n" RESET);
    #endif

    exit(exit_code);
  }
  else{
    #ifdef DEBUG
    printf (YEL "PPOS: task_exit    -  Exiting task %d\n" RESET, curr_task->id);
    #endif

    if(curr_task->waiting != NULL){
      task_t *first = curr_task->waiting;
      task_t *aux = first;
      do{
        aux = aux->next;
        task_resume(aux, &(curr_task->waiting));
      } while(aux != first);
    }

    //Remove tarefa da fila
    queue_remove((queue_t **)&readyTasks, (queue_t*)curr_task);
    user_tasks--;

    task_yield();
  }
}


/*
  Alterna a execução para a tarefa indicada
*/
int task_switch(task_t *task){
  if(task){
    //Salva task atual em old e nova task como atual
    task_t *aux_task = curr_task;
    curr_task = task;

    // #ifdef DEBUG
    // printf (YEL "PPOS: task_switch  -  Switching task %d -> %d\n" RESET, aux_task->id, task->id);
    // #endif

    curr_task->activations++;

    return (swapcontext(&(aux_task->context), &(task->context)));
  }

  return -1;
}


/*
  Larga a CPU e volta ao dispatcher
*/
void task_yield(){
  // #ifdef DEBUG
  // printf (YEL "PPOS: task_yield   -  Task %d yielded the CPU\n" RESET, curr_task->id);
  // #endif

  //Tarefa larga a CPU e chama o dispatcher
  task_switch(&dispatcher_task);
}


//------------------------------------------------------------------------------------------ P6 ------------------------------------------------------------------------------------//


/*
  Retorna tempo atual do relogio
*/
unsigned int systime (){
  return (sysClock);
}


//------------------------------------------------------------------------------------------ P8 ------------------------------------------------------------------------------------//


/*
  Suspende a tarefa atual, movendo ela da fila de prontas para a fila indicada
*/
void task_suspend (task_t **queue){
  if(queue){
    #ifdef DEBUG
    printf (GRN "PPOS: task_suspend -  Suspending task %d\n" RESET, curr_task->id);
    #endif
    
    int type = curr_task->task_type;
    curr_task->task_type = SYSTEM;

    queue_remove((queue_t **)&readyTasks, (queue_t*)curr_task);
    curr_task->status = SUSPENDED;
    queue_append((queue_t **)queue, (queue_t*)curr_task);
    curr_task->prio_d = curr_task->prio_s;

    curr_task->task_type = type;

    task_yield();
  }
}

/*
  Resume uma tarefa, colocando ela de volta na fila de prontas
*/
void task_resume (task_t *task, task_t **queue){
  if(queue && task){
    #ifdef DEBUG
    printf (GRN "PPOS: task_resume  -  Resuming task %d\n" RESET, task->id);
    #endif

    queue_remove((queue_t **)queue, (queue_t*)task);
    task->status = READY;
    queue_append((queue_t **)&readyTasks, (queue_t*)task);
  }
}

/*
  Suspende tarefa atual ate o fim da tarefa indicada
*/
int task_wait (task_t *task){
  if(task && task->status != TERMINATED){
    #ifdef DEBUG
    printf (GRN "PPOS: task_wait    -  Task %d is waiting for task %d\n" RESET, curr_task->id, task->id);
    #endif

    task_suspend(&(task->waiting));
    return task->exit_code;
  }

  return -1;
}


//------------------------------------------------------------------------------------------ P9 ------------------------------------------------------------------------------------//


/*
  Adormece uma tarefa por t milissegundos, desde que t > 0
*/
void task_sleep (int t){
  curr_task->wakeTime = systime() + t;

  #ifdef DEBUG
  printf (BLU "PPOS: task_sleep   -  Task %d will sleep until %dms\n" RESET, curr_task->id, curr_task->wakeTime);
  #endif

  if(t > 0){
    task_suspend((task_t **)&sleepingTaks);
  }
}


//------------------------------------------------------------------------------------------ P10 ------------------------------------------------------------------------------------//


/*
  Inicia um semaforo com contador igual a value
  Bloqueia a preempção tratando a tarefa como de sistema, depois a retornando ao tipo original
*/
int sem_init (semaphore_t *s, int value){
  //Bloqueia preempção
  int orig_type = curr_task->task_type;
  curr_task->task_type = SYSTEM;

  if(s && s->state == SEM_DEAD){
    s->cont = value;
    s->lock = 0;
    s->queue = NULL;
    s->state = SEM_ALIVE;

    curr_task->task_type = orig_type;
    return 0;
  }

  curr_task->task_type = orig_type;
  return -1;
}

/*
  Operacao de down em um semaforo, tenta acessar e caso o valor interno seja < 0, entra na fila
  Retorna 0 em caso de sucesso e -1 em caso de erro (semáforo não existe ou foi destruído)
*/
int sem_down (semaphore_t *s){
  //Bloqueia preempção
  int orig_type = curr_task->task_type;
  curr_task->task_type = SYSTEM;

  if(s && s->state == SEM_ALIVE){
    // busy waiting
    while (__sync_fetch_and_or ( &(s->lock), 1) ) {};
    s->cont--;
    if(s->cont < 0){
      //Semáforo cheio, suspende tarefa atual
      s->lock = 0;
      task_suspend( &(s->queue) );
    }
    s->lock = 0;

    curr_task->task_type = orig_type;
    return 0;
  }

  curr_task->task_type = orig_type;
  return -1;
}

/*
  Operacao de up em um semaforo, libera uma vaga no semaforo para alguem da fila
  Retorna 0 em caso de sucesso e -1 em caso de erro (semáforo não existe ou foi destruído)
*/
int sem_up (semaphore_t *s){
  //Bloqueia preempção
  int orig_type = curr_task->task_type;
  curr_task->task_type = SYSTEM;

  if(s && s->state == SEM_ALIVE){
    // busy waiting
    while (__sync_fetch_and_or ( &(s->lock), 1) ) {};
    s->cont++;
    if(s->cont <= 0){
      //Semáforo com vagas, acorda a primeira tarefa da fila
      task_resume( s->queue, &(s->queue) );
    }
    s->lock = 0;

    curr_task->task_type = orig_type;
    return 0;
  }

  curr_task->task_type = orig_type;
  return -1;
}

/*
  Destroi semaforo
  Retorna 0 em caso de sucesso e -1 em caso de erro (semáforo não existe ou já foi destruído)
*/
int sem_destroy (semaphore_t *s){
  //Bloqueia preempção
  int orig_type = curr_task->task_type;
  curr_task->task_type = SYSTEM;

  if(s){
    if(s->queue){
      task_t *first = s->queue;
      task_t *aux = first;
      task_t *prox;

      // Acorda todas as tarefas do semáforo
      do{
        prox = aux->next;
        task_resume(s->queue, &(s->queue));
        aux = prox;
      } while(s->queue != NULL);
    }
    s->state = SEM_DEAD;

    curr_task->task_type = orig_type;
    return 0;
  }

  curr_task->task_type = orig_type;
  return -1;
}
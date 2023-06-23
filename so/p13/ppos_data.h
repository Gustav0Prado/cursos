// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 1.5 -- Março de 2023

// Estruturas de dados internas do sistema operacional

#ifndef __PPOS_DATA__
#define __PPOS_DATA__

#include <ucontext.h>		// biblioteca POSIX de trocas de contexto

//Define cores para os printf's
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

// Macro para definir tipo da tarefa
#define SYSTEM 0
#define USER   1

// Quantum padrao eh de 20 "ticks"
#define DEFQUANTUM 10

// Define estados de "vida"
#define DEAD  0
#define ALIVE 1

// Tipo enumerado com estados das tarefas
typedef enum {
  READY, SUSPENDED, TERMINATED
} State_t ;

// Estrutura que define um Task Control Block (TCB)
typedef struct task_t
{
  struct task_t *prev, *next;		// ponteiros para usar em filas
  int id;				                // identificador da tarefa
  ucontext_t context;			      // contexto armazenado da tarefa
  State_t status;			          // pronta, rodando, suspensa, ...
  int exit_code;                // Exit code da tarefa
  int prio_d;                   // Prioridade dinamica
  int prio_s;                   // Prioridade estatica
  int task_type;                // Tipo da tarefa (User ou System)
  int quantum;                  // Quantum de uma tarefa
  int cpuTime;                  // Tempo de CPU usado pela tarefa
  int activations;              // Numero de vezes que tarefa foi ativada
  unsigned int creationTime;    //Marca de quando a tarefa foi criada
  struct task_t *waiting;       //Fila de tarefas esperando a tarefa atual terminar
  int wakeTime;                 //Instante de tempo em que a tarefa atual deve acordar
  int diskOP;                   // Operacao no disco
  int diskRet;                  // Retorno da OP no disco
  int diskBlock;                // Bloco a ser lido do disco
  void *diskBuffer;             // Buffer onde guardar bloco
  // ... (outros campos serão adicionados mais tarde)
} task_t ;

// estrutura que define um semáforo
typedef struct
{
  int state;                     //Semaforo esta destruido/não inicializado(0) ou inicializado(1)
  int cont;                      //Contador de vagas no semáforo
  short lock;                    //Trava do semaforo para acessá-lo
  task_t *queue;                 //Fila de tarefas travadas no semáforo
} semaphore_t ;

// estrutura que define um mutex
typedef struct
{
  // preencher quando necessário
} mutex_t ;

// estrutura que define uma barreira
typedef struct
{
  // preencher quando necessário
} barrier_t ;

// estrutura que define uma fila de mensagens
typedef struct
{
  int status;                   // Status da fila (inicializada ou terminada)
  int max_msgs;                 // Numero maximo de mensagens
  int msg_size;                 // Tamanho de cada mensagem
  void *buffer;                 // Buffer que armazena mensagens
  int bHead;                    // Head do buffer (escrita)
  int bTail;                    // Tail do buffer (leitura)
  int qtd_msgs;                 // Qtd de mensagens da fila
  semaphore_t sem_vaga;         // Semaforo interno da fila
  semaphore_t sem_buff;         // Semaforo interno da fila
  semaphore_t sem_item;         // Semaforo interno da fila
} mqueue_t ;

#endif


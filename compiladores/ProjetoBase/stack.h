#define TAM_PILHA 255

#define INTEIRO    0
#define BOOLEANO   1
#define INDEFINIDO 2

typedef struct{
   int tipos[TAM_PILHA];
   int topo;
} Pilha_t;

int iniciaPilha(Pilha_t *pilha);
int empilha(Pilha_t *pilha, int elem);
int desempilha(Pilha_t *pilha);
int finalizaPilha(Pilha_t *pilha);
void printPilha(Pilha_t *pilha);
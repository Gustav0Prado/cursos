#define TAM_PILHA 255

typedef struct{
   void *elem[TAM_PILHA];
   int topo;
} Pilha_t;

int iniciaPilha(Pilha_t *pilha);
int inserePilha(Pilha_t *pilha, void* elem);
void* desempilha(Pilha_t *pilha);
int finalizaPilha(Pilha_t *pilha);
void printPilha(Pilha_t *pilha);
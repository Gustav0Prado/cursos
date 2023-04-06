typedef struct Var_t{
   char *ident;
   struct Var_t *next;
} Var_t;

typedef struct{
   struct Var_t *top;
} Pilha_t;

Pilha_t *iniciaPilha();
int inserePilha(char *ident, Pilha_t *stack);
int removePilha(int n, Pilha_t *stack);
Var_t *buscaPilha(char *ident, Pilha_t *stack);
int finalizaPilha(Pilha_t *stack);
void printPilha(Pilha_t *stack);
int tamanhoPilha(Pilha_t *stack);
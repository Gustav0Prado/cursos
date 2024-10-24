#define m 11
#define VAZIO 0
#define FALSE 1
#define REMOVIDO 2

typedef struct Slot {
   int chave;
   int removido;
} tSlot;

typedef struct Tabela {
   tSlot T1[m];
   tSlot T2[m];
}tTabHash;

int inserir(tTabHash* T, int k);

int remover(tTabHash *T, int k);

void imprimeT(tTabHash T);
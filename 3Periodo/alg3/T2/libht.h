#define m 11
#define TRUE 1
#define FALSE 0

typedef struct Slot {
   int chave;
   int removido;
   int tabela;
   int posicao;
} tSlot;

typedef struct Tabela {
   tSlot* T1[m];
   tSlot* T2[m];
}tTabHash;

int inserir(tTabHash* T, int k);

int remover(tTabHash* T, int k);

void imprimeT(tTabHash T);

void destroiTabela(tTabHash T);
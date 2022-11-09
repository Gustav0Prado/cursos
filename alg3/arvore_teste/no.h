struct no{
   int chave;
   struct no *esq, *pai, *dir;
};
typedef struct no tNo;

struct arvore{
   tNo *raiz;
};
typedef struct arvore tArvore;
struct no{
   int chave;
   int nivel;
   int balanc;
   struct no *esq, *pai, *dir;
};
typedef struct no tNo;

/*funcao de busca binaria*/
tNo *busca(tNo *no, int chave);

/*funcao de inclusao*/
tNo *inclui(tNo *no, int chave);

/*funcao de exclusao*/
tNo *exclui(tNo *no, int chave);

/*funcao de impressao em ordem*/
void emOrdem(tNo *no);

/*destroi arvore e todos os nodos*/
void destroiArvore(tNo *no);

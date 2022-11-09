struct nodo_f {
    int id;
    struct nodo_f *prox;
};
typedef struct nodo_f NodoFila;

struct fila {
    NodoFila *ini;
    NodoFila *fim;
    int tamanho;
};
typedef struct fila Fila;

Fila*criaFila();

Fila* destroiFila(Fila *f);

int filaVazia(Fila *f);

int tamanhoFila(Fila *f);

int enfilera(Fila *f, int elemento);

int desenfilera(Fila *f);

void imprimeFila(Fila *f);

int primeiroFila(Fila *f);
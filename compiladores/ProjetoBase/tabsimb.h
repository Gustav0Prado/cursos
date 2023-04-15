typedef enum{
   INT,
   BOOL
} Tipo_e;

typedef struct Var_t{
   char *ident;
   struct Var_t *next;
   Tipo_e tipo;
   int deslocamento;
} Var_t;

typedef struct{
   struct Var_t *top;
} TabSimb_t;

void iniciaTabSimb(TabSimb_t *tab);
int insereTabSimb(char *ident, TabSimb_t *tab, int desloc);
int removeTabSimb(int n, TabSimb_t *tab);
Var_t *buscaTabSimb(char *ident, TabSimb_t *tab);
int finalizaTabSimb(TabSimb_t *tab);
void printTabSimb(TabSimb_t *tab);
int tamanhoTabSimb(TabSimb_t *tab);
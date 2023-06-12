#define VALOR 0
#define REF   1

#define PROC_PROC 0
#define PROC_FUNCTION 1

#define MAXP 64

// Enumerado com tipos possiveis
typedef enum{
   INT,
   BOOL,
   INDEF
} Tipo_e;

// Enumerado com tipos possiveis
typedef enum{
   VS,
   PFORM,
   PROC
} tipoSimb_e;

// Informacoes usadas nos parametros formais
typedef struct ParamF_t{
   Tipo_e tipo;
   int passagem;
} ParamF_t;

// Informacoes da tabela de simbolos para procedimentos
typedef struct Proc_t{
   int rotulo;
   int num_params;
   int passagem[MAXP];
   int tipo;
   int retorno;
} Proc_t;

// Informacoes da tabela de simbolos para variaveis simples
typedef struct VarS_t{
   Tipo_e tipo;
} VarS_t;

// Struct de cada simbolo da tabela
typedef struct Simb_t{
   char *ident;
   struct Simb_t *next;
   tipoSimb_e tipo;
   int nivel_lex;
   int deslocamento;
   union
   {
      VarS_t vs;
      Proc_t proc;
      ParamF_t parform;
   } uni;
   
} Simb_t;

typedef struct{
   struct Simb_t *top;
} TabSimb_t;

void iniciaTabSimb(TabSimb_t *tab);
int insereTabSimbVS(char *ident, TabSimb_t *tab, int desloc, int nv, int tipo);
int insereTabSimbProc(char *ident, TabSimb_t *tab, int desloc, int nl);
int removeTabSimb(int n, TabSimb_t *tab);
Simb_t *buscaTabSimb(char *ident, TabSimb_t *tab);
int finalizaTabSimb(TabSimb_t *tab);
void printTabSimb(TabSimb_t *tab);
int tamanhoTabSimb(TabSimb_t *tab);
void atualizaTipos(TabSimb_t *tab, int tipo);
int insereTabSimbParam(char *ident, TabSimb_t *tab, int pass, int nl, int desloc, int tipo);
void atualizaParams(TabSimb_t *tab, Simb_t *procm, int tipo);
int insereTabSimbFunc(char *ident, TabSimb_t *tab, int rot, int nl);
void atualizaFunc(TabSimb_t *tab, Simb_t *func, int tipo);
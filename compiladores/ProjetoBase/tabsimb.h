#define VALOR
#define REFERENCIA

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
} tipo_e;

// Informacoes usadas nos parametros formais
typedef struct ParamF_t{
   Tipo_e tipo;
   short passagem;
   int nivel_lex;
   int rotulo;
   int deslocamento;
} ParamF_t;

// Informacoes da tabela de simbolos para procedimentos
typedef struct Proc_t{
   int nivel_lex;
   int num_param;
   int rotulo;
} Proc_t;

// Informacoes da tabela de simbolos para variaveis simples
typedef struct VarS_t{
   Tipo_e tipo;
   int deslocamento;
   int nivel_lex;
} VarS_t;

// Struct de cada simbolo da tabela
typedef struct Simb_t{
   char *ident;
   struct Simb_t *next;
   tipo_e tipo;
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
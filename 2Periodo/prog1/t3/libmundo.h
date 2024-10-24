#include "liblef.h"
#include "libfila.h"
#include "libconjunto.h"

#define N_PESSOAS 100
#define N_LOCAIS 8

/*tipo pessoa*/
typedef struct pessoas {
   int id;
   int extroversao;
   int paciencia;
   int idade;
   conjunto_t *rumores;
} pessoa_t;

typedef struct coordenada{
   int x;
   int y;
} coord_t;

typedef struct locais {
   int id;
   int lotacao_max;
   coord_t localizacao;
   conjunto_t *publico;
   fila_t *fila;
} local_t;

/*struct de cehagada e saida e a mesma pois carregam os mesmos dados*/
typedef struct evt_c_s {
   int ID_PESSOA;
   int ID_LOCAL;
} evento_cs_t;

/*struct de cehagada e saida e a mesma pois carregam os mesmos dados*/
typedef struct evt_dissemina {
   int ID_PESSOA;
   int ID_LOCAL;
   conjunto_t* CJ_RUMOR;
} evento_diss_t;

/*estrutura de mundo*/
typedef struct mundo{
   pessoa_t PESSOAS[N_PESSOAS];
   local_t LOCAIS[N_LOCAIS];
   conjunto_t *CJ_RUMORES_MUNDO;
} mundo_t;



void imprime_l(lef_t *l);

/*Retorna numero aleatorio entre min e max*/
int ALEAT(int min, int max);

/*cria o conjunto de rumores com valores de 0 ate max*/
void cria_rumores(conjunto_t *CJ_RUMORES_MUNDO, int max);

int MAX(int a, int b);

void cria_chegada(lef_t *l, int ID_PESSOA, int ID_LOCAL, int TEMPO, mundo_t mundo);

void cria_chegada_inicio(lef_t *l, int ID_PESSOA, int ID_LOCAL, int TEMPO, mundo_t mundo);

void cria_saida(lef_t *l, int ID_PESSOA, int ID_LOCAL, int TEMPO, mundo_t mundo);

void cria_diss(lef_t *l, int ID_PESSOA, int ID_LOCAL, int TEMPO, conjunto_t *CJ_RUMOR, mundo_t mundo);

void cria_fim(lef_t *l, int TEMPO);

void trata_chegada(lef_t *l, evento_t *even, mundo_t meumundo);

void trata_saida(lef_t *l, evento_t *even, mundo_t mundo);

void trata_disseminacao(lef_t *l, evento_t *even, mundo_t mundo);
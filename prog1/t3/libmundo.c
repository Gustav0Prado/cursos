#include "libmundo.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define CHEGADA 0
#define SAIDA 1
#define DISSEMINACAO 2
#define FIM 3

/*arquivo com algumas funcoes auxiliares para o mundo*/

/*Retorna numero aleatorio entre min e max*/
int ALEAT(int min, int max){
   return ((rand() % (max - min + 1) + min));
}

/*cria o conjunto de rumores com valores de 0 ate max*/
void cria_rumores(conjunto_t *CJ_RUMORES_MUNDO, int max){
   for(int i = 0; i < max; i++){
      insere_conjunto(CJ_RUMORES_MUNDO, i);
   }
}

/*retorna o maior numero entre a e b*/
int MAX(int a, int b){
   if(a > b){
      return a;
   }
   return b;
}

/*cra evento de chegada em ordem na lef*/
void cria_chegada(lef_t *l, int ID_PESSOA, int ID_LOCAL, int TEMPO, mundo_t mundo){
   evento_t evt;
   evento_cs_t aux_chega_sai;

   evt.tempo = TEMPO;
   evt.tipo = CHEGADA;
   evt.tamanho = sizeof(evento_cs_t);
   aux_chega_sai.ID_LOCAL = ID_LOCAL;
   aux_chega_sai.ID_PESSOA = ID_PESSOA;
   evt.dados = &aux_chega_sai;
   adiciona_ordem_lef(l, &evt);
}

/*cria chegada no inicio da lef*/
void cria_chegada_inicio(lef_t *l, int ID_PESSOA, int ID_LOCAL, int TEMPO, mundo_t mundo){
   evento_t evt;
   evento_cs_t aux_chega_sai;

   evt.tempo = TEMPO;
   evt.tipo = CHEGADA;
   evt.tamanho = sizeof(evento_cs_t);
   aux_chega_sai.ID_LOCAL = ID_LOCAL;
   aux_chega_sai.ID_PESSOA = ID_PESSOA;
   evt.dados = &aux_chega_sai;
   adiciona_inicio_lef(l, &evt);
}

/*cria evento de saida em ordem na lef*/
void cria_saida(lef_t *l, int ID_PESSOA, int ID_LOCAL, int TEMPO, mundo_t mundo){
   evento_t evt;
   evento_cs_t aux_chega_sai;

   evt.tempo = TEMPO;
   evt.tipo = SAIDA;
   evt.tamanho = sizeof(evento_cs_t);
   aux_chega_sai.ID_LOCAL = ID_LOCAL;
   aux_chega_sai.ID_PESSOA = ID_PESSOA;
   evt.dados = &aux_chega_sai;
   adiciona_ordem_lef(l, &evt);
}

/*cria evento de disseminacao na lef*/
void cria_diss(lef_t *l, int ID_PESSOA, int ID_LOCAL, int TEMPO, conjunto_t *CJ_RUMOR, mundo_t mundo){
   evento_t evt;
   evento_diss_t aux_diss_rumor;

   evt.tempo = TEMPO;
   evt.tipo = DISSEMINACAO;
   evt.tamanho = sizeof(evento_diss_t);
   aux_diss_rumor.ID_LOCAL = ID_LOCAL;
   aux_diss_rumor.ID_PESSOA = ID_PESSOA;
   aux_diss_rumor.CJ_RUMOR = CJ_RUMOR;
   evt.dados = &aux_diss_rumor;
   adiciona_ordem_lef(l, &evt);
}

void cria_fim(lef_t *l, int TEMPO){
   evento_t evt;

   evt.tempo = TEMPO;
   evt.tipo = FIM;
   evt.tamanho = 0;
   adiciona_ordem_lef(l, &evt);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*tratamento para um evento de chegadad*/
void trata_chegada(lef_t *l, evento_t *even, mundo_t mundo){
   int TPL, NRD;
   conjunto_t *SUBCJ_RUMOR;
   evento_cs_t *ptr_tipo_evt = even->dados;

   /*dados do evento*/
   int ID_PESSOA = ptr_tipo_evt->ID_PESSOA;
   int ID_LOCAL = ptr_tipo_evt->ID_LOCAL;
   int TEMPO_ATUAL = even->tempo;

   /*local lotado*/
   if(mundo.LOCAIS[ID_LOCAL].lotacao_max == cardinalidade(mundo.LOCAIS[ID_LOCAL].publico)){
      /*entra na fila*/
      if(mundo.PESSOAS[ID_PESSOA].paciencia/4 - tamanho_fila(mundo.LOCAIS[ID_LOCAL].fila) > 0){
         insere_fila(mundo.LOCAIS[ID_LOCAL].fila, ID_PESSOA);

         printf("%6d:CHEGA Pessoa %4d Local %2d (%2d/%2d), FILA %2d\n",
         TEMPO_ATUAL, ID_PESSOA, ID_LOCAL, cardinalidade(mundo.LOCAIS[ID_LOCAL].publico), mundo.LOCAIS[ID_LOCAL].lotacao_max,
         tamanho_fila(mundo.LOCAIS[ID_LOCAL].fila));
      }
      else{
         /*desiste da fila*/
         printf("%6d:CHEGA Pessoa %4d Local %2d (%2d/%2d), DESISTE\n",
         TEMPO_ATUAL, ID_PESSOA, ID_LOCAL, cardinalidade(mundo.LOCAIS[ID_LOCAL].publico), mundo.LOCAIS[ID_LOCAL].lotacao_max);

         cria_saida(l, ID_PESSOA, ID_LOCAL, TEMPO_ATUAL, mundo);
      }
   }
   /*local nao lotado*/
   else{
      /*mensagem*/
      printf("%6d:CHEGA Pessoa %4d Local %2d (%2d/%2d), ENTRA\n",
      TEMPO_ATUAL, ID_PESSOA, ID_LOCAL, cardinalidade(mundo.LOCAIS[ID_LOCAL].publico), mundo.LOCAIS[ID_LOCAL].lotacao_max);


      insere_conjunto(mundo.LOCAIS[ID_LOCAL].publico, ID_PESSOA);

      TPL = MAX(1, ((mundo.PESSOAS[ID_PESSOA].paciencia/10)+ALEAT(-2,6)));

      NRD = mundo.PESSOAS[ID_PESSOA].extroversao/10;
      SUBCJ_RUMOR = cria_subconjunto(mundo.PESSOAS[ID_PESSOA].rumores, NRD);
      /*cria evento de disseminacao*/
      cria_diss(l, ID_PESSOA, ID_LOCAL, TEMPO_ATUAL+ALEAT(0,TPL), SUBCJ_RUMOR, mundo);
      cria_saida(l, ID_PESSOA, ID_LOCAL, TEMPO_ATUAL+TPL, mundo);
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void trata_saida(lef_t *l, evento_t *even, mundo_t mundo){
   int ID_PESSOA_FILA, ID_LOCAL_DEST, DIST_X, DIST_Y, DISTANCIA, TDL;
   evento_cs_t *ptr_tipo_evt = even->dados;

   /*dados do evento*/
   int ID_PESSOA = ptr_tipo_evt->ID_PESSOA;
   int ID_LOCAL = ptr_tipo_evt->ID_LOCAL;
   int TEMPO_ATUAL = even->tempo;

   /*caso a saida seja de alguem que estava no local*/
   if(pertence(mundo.LOCAIS[ID_LOCAL].publico, ID_PESSOA)){
      retira_conjunto(mundo.LOCAIS[ID_LOCAL].publico, ID_PESSOA);
      if(!fila_vazia(mundo.LOCAIS[ID_LOCAL].fila)){
         /*cria evento de chegada e insere em primeiro*/
         retira_fila(mundo.LOCAIS[ID_LOCAL].fila, &ID_PESSOA_FILA);

         printf("%6d:SAIDA Pessoa %4d Local %2d (%2d/%2d) REMOVE FILA Pessoa %2d\n",
         TEMPO_ATUAL, ID_PESSOA, ID_LOCAL, cardinalidade(mundo.LOCAIS[ID_LOCAL].publico), mundo.LOCAIS[ID_LOCAL].lotacao_max,
         ID_PESSOA_FILA);
         
         cria_chegada_inicio(l, ID_PESSOA_FILA, ID_LOCAL, TEMPO_ATUAL+0, mundo);
      }
      else{
         printf("%6d:SAIDA Pessoa %4d Local %2d (%2d/%2d)\n",
         TEMPO_ATUAL, ID_PESSOA, ID_LOCAL, cardinalidade(mundo.LOCAIS[ID_LOCAL].publico), mundo.LOCAIS[ID_LOCAL].lotacao_max);
      }
   }
   /*pessoa desistiu da fila*/
   else{
      retira_fila(mundo.LOCAIS[ID_LOCAL].fila, &ID_PESSOA);
   }
   /*cria evento de chegada em outro lugar aleatorio*/
   ID_LOCAL_DEST = ALEAT(0, 7);
   DIST_X = mundo.LOCAIS[ID_LOCAL_DEST].localizacao.x - mundo.LOCAIS[ID_LOCAL].localizacao.x;
   DIST_Y = mundo.LOCAIS[ID_LOCAL_DEST].localizacao.y - mundo.LOCAIS[ID_LOCAL].localizacao.y;
   DISTANCIA = sqrt((DIST_X*DIST_X)+(DIST_Y*DIST_Y));
   TDL = DISTANCIA/(100-MAX(0, mundo.PESSOAS[ID_PESSOA].idade-40));
   cria_chegada(l, ID_PESSOA, ID_LOCAL_DEST, TEMPO_ATUAL+TDL/15, mundo);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

/*tratamento para um evento de disseminacao*/
void trata_disseminacao(lef_t *l, evento_t *even, mundo_t mundo){
   int ID_PESSOA_ESCUTA, ID_RUMOR;
   evento_diss_t *ptr_tipo_evt = even->dados;

   /*dados do evento*/
   int ID_PESSOA = ptr_tipo_evt->ID_PESSOA;
   int ID_LOCAL = ptr_tipo_evt->ID_LOCAL;
   conjunto_t* CJ_RUMOR = ptr_tipo_evt->CJ_RUMOR;
   int TEMPO_ATUAL = even->tempo;

   /*para cada pessoa do local, tenta espalhar os rumores*/
   iniciar_iterador(mundo.LOCAIS[ID_LOCAL].publico);

   printf("%6d:RUMOR Pessoa %4d Local %2d ", TEMPO_ATUAL, ID_PESSOA, ID_LOCAL);

   /*passa por todas as pessoas do conjunto publico enquanto o CJ_RUMOR nao for vazio*/
   while(incrementar_iterador(mundo.LOCAIS[ID_LOCAL].publico, &ID_PESSOA_ESCUTA) && !conjunto_vazio(CJ_RUMOR)){
      if( ALEAT(0, 100) < mundo.PESSOAS[ID_PESSOA_ESCUTA].extroversao && ID_PESSOA_ESCUTA != ID_PESSOA){
         ID_RUMOR = retirar_um_elemento(CJ_RUMOR);
         insere_conjunto(mundo.PESSOAS[ID_PESSOA_ESCUTA].rumores, ID_RUMOR);
         
         printf("(P%d:R%d) ", ID_PESSOA_ESCUTA, ID_RUMOR);
      }
      /*se nao, apenas ignora*/
   }
   printf("\n");

   /*destroi subconjunto de rumores apos utilizar*/
   CJ_RUMOR = destroi_conjunto(CJ_RUMOR);
}
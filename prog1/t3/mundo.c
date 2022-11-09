#include "libmundo.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*constantes*/
#define T_INICIAL 0
#define N_TAMANHO_MUNDO 20000
#define N_RUMORES_MUNDO 30
#define FIM_DO_MUNDO 34944
#define CHEGADA 0
#define SAIDA 1
#define DISSEMINACAO 2
#define FIM 3

int main(){
   lef_t *l = cria_lef();
   mundo_t meumundo;
   meumundo.CJ_RUMORES_MUNDO = cria_conjunto(N_RUMORES_MUNDO);
   evento_t *even;

   if(l != NULL && meumundo.CJ_RUMORES_MUNDO != NULL){
      srand(time(0));
      cria_rumores(meumundo.CJ_RUMORES_MUNDO, N_RUMORES_MUNDO);

      /*inicializa as pessoas*/
      for(int i = 0; i < N_PESSOAS; i++){
         meumundo.PESSOAS[i].id = i;
         meumundo.PESSOAS[i].extroversao = ALEAT(0, 100);
         meumundo.PESSOAS[i].paciencia = ALEAT(0, 100);
         meumundo.PESSOAS[i].idade = ALEAT(18, 100);
         meumundo.PESSOAS[i].rumores = cria_subconjunto(meumundo.CJ_RUMORES_MUNDO, ALEAT(1, 5));
      }

      /*incicializa locais*/
      for(int i = 0; i < N_LOCAIS; i++){
         meumundo.LOCAIS[i].id = i;
         meumundo.LOCAIS[i].lotacao_max = ALEAT(5, 30);
         meumundo.LOCAIS[i].localizacao.x = ALEAT(0, N_TAMANHO_MUNDO-1);
         meumundo.LOCAIS[i].localizacao.y = ALEAT(0, N_TAMANHO_MUNDO-1);
         meumundo.LOCAIS[i].publico = cria_conjunto(meumundo.LOCAIS[i].lotacao_max);
         meumundo.LOCAIS[i].fila = cria_fila();
      }
      
      /*cria chegadas em tempo aleatorios para cada pessoa do mundo*/
      for(int i = 0; i < N_PESSOAS; i++){
         cria_chegada(l, i, ALEAT(0, N_LOCAIS-1), ALEAT(0, 96*7), meumundo);
      }

      //insere fim do mundo na lef;
      cria_fim(l, FIM_DO_MUNDO);

      /*parte principal/eventos*/
      even = obtem_primeiro_lef(l);
      while(even != NULL){
         switch (even->tipo){
            case CHEGADA:
               trata_chegada(l, even, meumundo);
               break;

            case SAIDA:
               trata_saida(l, even, meumundo);
               break;

            case DISSEMINACAO:
               trata_disseminacao(l, even, meumundo);
               break;

            case FIM:
               printf("%6d:FIM\n", even->tempo);
               l = destroi_lef(l);

               for(int i = 0; i < N_PESSOAS; i++){
                  meumundo.PESSOAS[i].rumores = destroi_conjunto(meumundo.PESSOAS[i].rumores);
               }

               /*incicializa locais*/
               for(int i = 0; i < N_LOCAIS; i++){
                  meumundo.LOCAIS[i].publico = destroi_conjunto(meumundo.LOCAIS[i].publico);
                  meumundo.LOCAIS[i].fila = destroi_fila(meumundo.LOCAIS[i].fila);
               }
               
               meumundo.CJ_RUMORES_MUNDO = destroi_conjunto(meumundo.CJ_RUMORES_MUNDO);

               free(even);
               return 0;
         }
         free(even->dados);
         free(even);
         /*proximo evento da lef*/
         even = obtem_primeiro_lef(l);
      }
   }
   return 1;
}
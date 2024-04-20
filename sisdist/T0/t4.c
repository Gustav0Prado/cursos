/* Autor: Elias P. Duarte Jr.
Data da Última Modificação: 11/abril/2024
Descrição: Nosso primeiro programa de simulação da disciplina Sistemas Distribuídos.
   Vamos simular N processos, cada um conta o “tempo” independentemente
   Um exemplo simples e significativo para captar o “espírito” da simulação */

#include <stdio.h>
#include <stdlib.h>
#include "smpl.h"

// Vamos definir os EVENTOS 
#define test 1
#define fault 2
#define recovery 3

#define unknown -1
#define correct  0
#define failed   1

// Vamos definir o descritor do processo

typedef struct{ 
   int id;           // identificador de facility do SMPL
   int* STATE;       // Vetor de estados
   // outras variáveis locais dos processos são declaradas aqui!
} TipoProcesso;

TipoProcesso *processo;

int main (int argc, char *argv[]) {

   static int N,   // número de processos
         token,  // indica o processo que está executando
         event, r, i,
         MaxTempoSimulac = 150;

   static char fa_name[5];

   if (argc != 2) {
         puts("Uso correto: tempo <número de processos>");
         exit(1);
      }

   N = atoi(argv[1]);

   smpl(0, "Um Exemplo de Simulação");
   reset();
   stream(1);

   // inicializar processos

   processo = (TipoProcesso *) malloc(sizeof(TipoProcesso)*N);
   for (i=0; i<N; i++) {
      processo[i].STATE = malloc(sizeof(int)*N);           // Aloca um inteiro para cada processo
      memset (processo[i].STATE, unknown, sizeof(int)*N);  // Inicia estados como unknown
      processo[i].STATE[i] = correct;                      // Inicia a si mesmo como correto
   }

   for (i=0; i<N; i++) {
      memset(fa_name, '\0', 5);
      sprintf(fa_name, "%d", i);
      processo[i].id = facility(fa_name,1);
   }
   // vamos fazer o escalonamento inicial de eventos

   // nossos processos vão executar testes em intervalos de testes
   // o intervalo de testes vai ser de 30 unidades de tempo
   // a simulação começa no tempo 0 (zero) e vamos escalonar o primeiro teste de todos os    
   //       processos para o tempo 30.0

   for (i=0; i<N; i++) {
      schedule(test, 30.0, i); 
   }
   schedule(fault, 31.0, 1);
   schedule(recovery, 61.0, 1);

   // agora vem o loop principal do simulador

   puts("===============================================================");
   puts("           Sistemas Distribuídos Prof. Elias");
   puts("          LOG do Trabalho Prático 0, Tarefa 0");
   puts("      Digitar, compilar e executar o programa tempo.c");
   printf("   Este programa foi executado para: N=%d processos.\n", N); 
   printf("           Tempo Total de Simulação = %d\n", MaxTempoSimulac);
   puts("===============================================================");

   while(time() < MaxTempoSimulac) {
      cause(&event, &token);
      
      int falhos = 0;      // Num de processos falhos
      int i = (token+1)%N; // Proximo processo a ser olhado

      switch(event) {
         case test: 
            if (status(processo[token].id) !=0) break; // se o processo está falho, não testa!
            printf("Processo %d: estou testando no tempo %4.1f\n", token, time());

            // Imprime vetor STATE[N]
            printf("\tAntes:  STATE[%d] = [ ", token);
            for(int j = 0; j < N; ++j) printf("%2d ", processo[token].STATE[j]);
            printf("]\n");

            // Olha os outros processos
            while ((i != token) && (falhos < N-1)){
               if(status(processo[i].id) == 0){
                  printf("\tSou %d e testei %d correto no tempo %4.1f\n", token, i, time());
                  processo[token].STATE[i] = correct;
                  
                  // Obtem infos dos outros processos, tirando a si mesmo e o que acabou de ser testado
                  for (int k = (i+1)%N; k != token; k = (k + 1) % N){
                     processo[token].STATE[k] = processo[i].STATE[k];
                  }

                  break;
               }
               else{
                  printf("\tSou %d e testei %d falho no tempo %4.1f\n", token, i, time());
                  processo[token].STATE[i] = failed;
                  falhos++;
               }
               i = (i + 1) % N; // Proximo processo
            }
            
            // Imprime vetor STATE[N]
            printf("\tDepois: STATE[%d] = [ ", token);
            for(int j = 0; j < N; ++j) printf("%2d ", processo[token].STATE[j]);
            printf("]\n");

            if (falhos == N-1) printf("\tTodos os demais processos estão falhos!!\n");
            
            schedule(test, 30.0, token);
            break;
         case fault:
            r = request(processo[token].id, token, 0);
            printf("Socooorro!!! Sou o processo %d  e estou falhando no tempo %4.1f\n", token, time());
            break;
         case recovery:
            release(processo[token].id, token);
            printf("Viva!!! Sou o processo %d e acabo de recuperar no tempo %4.1f\n", token, time());
            schedule(test, 1.0, token);
            break;
      } // switch
   } // while

   for(int i = 0; i < N; ++i) {
      free(processo[i].STATE);
   }
   free(processo);
} // tempo.c
      

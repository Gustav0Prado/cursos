/* Gustavo do Prado Siva
   GRR20203942*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include "bike.h"
#include "opcoes.h"
#include "learquivos.h"

int main(int argc, char* argv[]){
   DIR *dirlog;
   t_ListaBike *ListaBike;
   int opcao;

   /*entrada correta, abre o diretorio*/
   if(argc >= 2 && strcmp(argv[1], "-d") == 0){
      dirlog = opendir(argv[2]);
      if(!dirlog){
         printf("Erro ao ler diretorio\n");
         exit(1);
      }
      
      printf("Lendo Arquivos...\n");
      /*le arquivos e depois fecha diretorio*/
      ListaBike = leDir(dirlog, argv[2]);
      closedir(dirlog);

      /*Continua apenas se achou algum log*/
      if(ListaBike != NULL){
         imprimeOpcoes();
         printf("\nDigite a entrada desejada: ");

         /*scanf aceita apenas numeros inteiros*/
         while(scanf("%d", &opcao) == 1 && opcao != 7){
            switch (opcao){
               case 1:
                  opcao1(ListaBike);
                  break;
               case 2:
                  opcao2(ListaBike);
                  break;
               case 3:
                  opcao3(ListaBike);
                  break;
               case 4:
                  opcao4(ListaBike);
                  break;
               case 5:
                  opcao5(ListaBike, ListaBike->numLog);
                  break;
               case 6:
                  opcao6(ListaBike);
                  break;
            }

            imprimeOpcoes();
            printf("\nDigite a entrada desejada: ");
         }

         desaloca(ListaBike);
      }
      else{
         printf("Nenhum log encontrado\n");
      }
   }
   else{
      printf("Digite ./gps -d diretorio, para ler os logs do mesmo\n");
   }

   return 0;
}
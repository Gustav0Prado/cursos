/* Gustavo do Prado Siva
   GRR20203942*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "bike.h"
#include "learquivos.h"

/*Recebe uma linha e um registro de bicicleta, acha o primeiro separador(espaço)
e a partir dele, atribui a string ao modelo da bicicleta*/
char *leToken(char* linha){
   strtok(linha, " \n");
   return strtok(NULL, "\n");
}

/*retorna 1 se as duas primeiras linhas estao no padraoe 0 caso contrario*/
int logInvalido(FILE *arq){
   char gear[LSIZE];
   char data[LSIZE];
   char *modelo;
   char *dia;

   fgets(gear, LSIZE, arq);
   modelo = leToken(gear);
   /*modelo faltando*/
   if(strcmp(strtok(gear, ":"), "Gear") != 0 || modelo == NULL || modelo[0] == ' '){
      return 1;
   }
   fgets(data, LSIZE, arq);
   dia = strtok(data, ", ");
   dia = strtok(NULL, ",");
   /*data faltando ou incompleta*/
   if(strcmp(strtok(data, ":"), "Date") != 0 || dia == NULL || strlen(dia) < 5){
      return 1;
   }

   return 0;
}

/*verifica se eh um arquivo com extensao log*/
int ehlog(int tipo, char* nome){
   return (tipo == DT_REG && strstr(nome, ".log") != NULL) == 1;
}

/*cria no dado um modelo de Bike passado*/
t_Bike *criaNo(char *modelo){
   t_Bike *no = malloc(sizeof(t_Bike));

   if(no != NULL){
      no->tam = 1;
      no->max = NLOGS;
      no->VetorLog = malloc(sizeof(t_LogBike)*NLOGS);
      no->prox = NULL;
      strcpy(no->Modelo, modelo);
      no->distT = 0;
      no->pedalC = 0;
      no->pedalL = 0;
   }

   return no;
}

/*insere no no final da lista*/
int insereNo(t_Bike *no, t_ListaBike *lista){
   lista->fim->prox = no;
   lista->fim = no;

   return 0;
}

/*procura por um modelo de bike na lista, retornando o endereço dela ou NULL se não existir*/
t_Bike *procuraBike(char *modelo, t_ListaBike *lista){
   t_Bike *aux = lista->ini;

   while(aux != NULL && strcmp(aux->Modelo, modelo) != 0){
      aux = aux->prox;
   }
   return aux;
}

/*aloca lista caso seja nula, cria bike e insere na lista caso seja nova
ou cria/realoca log caso já exista*/
t_Bike *aloca(t_ListaBike **lista, FILE *arq){
   char *modelo;
   char linha[LSIZE+1];
   t_Bike *aux, *maux;
   t_LogBike *raux;
   t_ListaBike *ptrlista = *lista;

   if(*lista == NULL){
      fgets(linha, LSIZE, arq);
      modelo = leToken(linha);
      *lista = malloc(sizeof(t_ListaBike));
      /*atualiza ponteiro*/
      ptrlista = *lista;
      ptrlista->ini = criaNo(modelo);
      ptrlista->fim = ptrlista->ini;
      ptrlista->numLog = 0;
      aux = ptrlista->ini;
   }
   else{
      fgets(linha, LSIZE, arq);
      modelo = leToken(linha);
      aux = procuraBike(modelo, ptrlista);
      /*bike ja existe, adiciona ou realoca logs*/
      if(aux != NULL){
         if(aux->tam == aux->max){
            raux = realloc(aux->VetorLog, 2*aux->max*sizeof(t_LogBike));
            if(raux != NULL){
               aux->VetorLog = raux;
               aux->max = aux->max * 2;
            }
            else{
               printf("Erro ao realocar vetor de logs!\n");
               exit(1);
            }
         }
         aux->tam++;
      }
      /*bike nao existe*/
      else{
         maux = criaNo(modelo);
         if(maux != NULL){
            aux = maux;
            insereNo(aux, ptrlista);
         }
         else{
            printf("Erro ao criar bike!\n");
            exit(1);
         }
      }
   }

   return aux;
}

/*zera valores de um log o vetor*/
void zeraLog(t_Bike *aux, int posLog){
   memset(&(aux->VetorLog[posLog]), 0, sizeof(t_LogBike));
}

/*compara e calcula dados gerais da bicicleta: Distancia total, pedal mais curto
 e pedal mais longo*/
int calculaInfos(t_Bike *aux, int plog){
   /*inicia dados com o da primeira atividade da bicicleta*/
   if(aux->tam == 1){
      aux->pedalC = aux->VetorLog[0].Distancia;
      aux->pedalL = aux->VetorLog[0].Distancia;
      aux->distT = aux->VetorLog[0].Distancia;
   }
   /*depois compara e atualiza*/
   else{
      if(aux->VetorLog[plog].Distancia < aux->pedalC){
         aux->pedalC = aux->VetorLog[plog].Distancia;
      }
      else if(aux->VetorLog[plog].Distancia > aux->pedalL){
         aux->pedalL = aux->VetorLog[plog].Distancia;
      }
      aux->distT += aux->VetorLog[plog].Distancia;
   }

   return 0;
}

/*varre o diretorio e le os logs*/
t_ListaBike *leDir(DIR *dirlog, char *argv){
   t_ListaBike *ListaBike = NULL;
   t_Bike *atual;
   FILE *arq;
   struct dirent *entdir;
   int posLog = 0;
   char DirArq[101];

   while((entdir = readdir(dirlog)) != NULL){
      if(ehlog(entdir->d_type, entdir->d_name)){
         /*concatena nome do arquivo com nome do diretorio
         e manda para funcao de leitura*/
         strcpy(DirArq, argv);
         strcat(DirArq, entdir->d_name);

         /*abre arquivo de log*/
         arq = fopen(DirArq, "r");
         if(!arq){
            printf("Erro ao abrir arquivo de log\n");
            exit(1);
         }

         /*caso primeiras linhas estejam fora do padrao, pula o arquivo
         senao retorna ao inicio e continua*/
         if(logInvalido(arq)){
            printf("Arquivo de log invalido\n");
            fclose(arq);
            continue;
         }            
         rewind(arq);
         
         /*Aloca a primeira bike com o espaco padrao*/
         atual = aloca(&ListaBike, arq);
         
         if(atual != NULL){
            posLog = atual->tam-1;
            zeraLog(atual, posLog);
            learquivo(atual->VetorLog, posLog, arq);
            calculaInfos(atual, posLog);
            ListaBike->numLog++;
         }

         fclose(arq);
      }
   }
   return ListaBike;
}

/*desaloca ponteiros e retorna 0 em caso de sucesso*/
int desaloca(t_ListaBike *lista){
   t_Bike *aux = lista->ini;
   t_Bike *prox;

   while(aux != NULL){
      free(aux->VetorLog);
      prox = aux->prox;
      free(aux);
      aux = prox;
   }
   free(lista);

   return (lista == NULL);
}
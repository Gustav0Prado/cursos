/* Gustavo do Prado Siva
   GRR20203942*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bike.h"

#define NCAMPOS 6

int ehHora(char *hora){
   char *doisp;
   
   if(hora != NULL){
      doisp = strchr(hora, ':');
      doisp = strchr(doisp+1, ':');
      if(strlen(hora) == 8 && doisp != NULL){
         return 1;
      }
   }
   return 0;
}

/*transforma string de hora em inteiro de segundos*/
int horaToSeg(char *hora){
   char time[9];
   char *tok;
   int h, m, s;

   if(ehHora(hora)){
      strcpy(time, hora);
      tok = strtok(time, ":");
      h = atoi(tok);
      tok = strtok(NULL, ":");
      m = atoi(tok);
      tok = strtok(NULL, "\0");
      s = atoi(tok);	
      
      return (h*3600 + m*60 + s);
   }
   return 0;
}

/*Recebe uma linha e um registro de bicicleta, acha atraves dos separadores(espacos) 
a data por exntenso (char) e converte para dois inteiros mes e dia*/
int leData(t_LogBike vet[], int posLog, char* tok){
   char *meses[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
   char dataExtMes[4];
   int dia, i = 0;

   /*copia caracteres da data a partir do token*/
   tok = strtok(NULL, ":, ");
   strcpy(dataExtMes, tok);
   
   tok = strtok(NULL, ":, ");
   dia = atoi(tok);
   /*caso dia sejafora do comum, substitui por 0*/
   if(dia < 0 || dia > 31){
      vet[posLog].Dia = 0;
   }
   else{
      vet[posLog].Dia = dia;
   }

   /*busca no vetor meses*/
   while(i < 12 && strcmp(meses[i], dataExtMes) != 0){
		i++;
	}
	if(i <= 12){
      vet[posLog].Mes = i+1;
   }
   else{
      vet[posLog].Mes = 0;
   }

   return 0;
}

/*atualiza a estrutura hora, procurando na linha o char ':' como indicardor*/
int atualizaHora(char *tok, t_Hora *hora){
   tok = strtok(NULL, "\n");

   if(hora->ini == 0){
      hora->ini = horaToSeg(tok);
   }
   if(hora->ult > 0){
      hora->ult = hora->atual;
      hora->atual = horaToSeg(tok);
   }
   else{
      hora->atual = horaToSeg(tok);
      hora->ult = hora->atual;
   }

   return 0;
}

/*funcao atualiza media baseado no valor atual, aumentando a media ponderada, ou o numero de zeros*/
int atualizaMedia(t_Hora hora, t_Media *media){
   int peso = hora.atual - hora.ult;

   if(media->ult == 0){
      media->ult = media->atual;
   }
   else if(media->ult > 0){
      media->media += media->ult*peso;
      media->peso += peso;
      media->ult = media->atual;
   }
   return 0;
}

/*caso a media seja 0, retorna 0, caso contrário retorna a media aritmetica*/
double calculaMedia(t_Hora hora, t_Media *media){
   if(media->media == 0){
      return 0;
   }
   return (media->media)/ (media->peso);
}

/*passa pelas linhas do arquivo, procurando por alguma palavra chave*/
int learquivo(t_LogBike vet[], int posLog, FILE *arq){
   char linha[LSIZE+1];
   char *campos[NCAMPOS] = {"distance", "speed", "heart_rate", "cadence", "altitude", "timestamp"};
   double valorLinha;
   double subidaAnt = 0;
   char *tok;

   t_Hora hora = {0};
   t_Media cadM = {0};
   t_Media hrM = {0};
   t_Media velM = {0};

   fgets(linha, LSIZE, arq);
   tok = strtok(linha, ":, ");
   leData(vet, posLog, tok);
   
   while(!feof(arq)){
      fgets(linha, LSIZE, arq);
      tok = strtok(linha, ":, ");
      /*ignora linhas vazias*/
      if(tok != NULL){
         for(int i = 0; i < NCAMPOS; i++){
            /*caso ache algum campo de interesse, converte o valor da linha para float,
            mas despreza valores negativos e valores que nao aparecem (tok eh um \n ou espaco)*/
            if(strcmp(tok, campos[i]) == 0){
               tok = strtok(NULL, ":, ");
               if(tok != NULL){
                  valorLinha = atof(tok);
                  if(valorLinha >= 0){
                     switch (i){
                     case 0:
                        /*Guarda distancia em quilometros (divide por mil)*/
                        vet[posLog].Distancia = valorLinha/1000;
                        break;
                     case 1:
                        /*multiplica velocidade para km/h*/
                        if(vet[posLog].VelocidadeMax < valorLinha*3.6){
                           vet[posLog].VelocidadeMax = valorLinha*3.6;
                        }
                        velM.atual = valorLinha;
                        break;
                     case 2:
                        if(vet[posLog].HRmax < valorLinha){
                           vet[posLog].HRmax = valorLinha;
                        }
                        hrM.atual = valorLinha;
                        break;
                     case 3:
                        /*despreza valor de fractional cadence, mesmo com cadence no nome*/
                        if(strstr(linha, "fractional_cadence") == NULL){
                           cadM.atual = valorLinha;
                        }
                        break;
                     case 4:
                        /*guarda o acumulo da diferenca de altitudes (atual - anterior) 
                        caso atual > anterior*/
                        if(subidaAnt == 0.0){
                           subidaAnt = valorLinha;
                        }
                        else if(valorLinha > subidaAnt){
                           vet[posLog].SubidaAcum += valorLinha - subidaAnt;
                        }
                        subidaAnt = valorLinha;
                        break;
                     case 5:
                        /*atualiza valor atual de hora e usa para calcular medias ponderadas*/
                        atualizaHora(tok, &hora);
                        atualizaMedia(hora, &cadM);
                        atualizaMedia(hora, &hrM);
                        atualizaMedia(hora, &velM);
                        break;
                     }
                  }
               }
            }
         }
      }
   }

   /*calcula as media dos elementos*/
   vet[posLog].Cadencia = calculaMedia(hora, &cadM);
   vet[posLog].HRmedio = calculaMedia(hora, &hrM);
   vet[posLog].VelocidadeMed = calculaMedia(hora, &velM)*3.6;

   return 0;
}
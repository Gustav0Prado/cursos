/* Gustavo do Prado Siva
   GRR20203942*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bike.h"
#include "learquivos.h"

/*imprime na tela as opcoes do programa*/
void imprimeOpcoes(){
   printf("\n\n");
   printf("1 - Mostrar todas as bicicletas\n");
   printf("2 - Buscar por bicicleta\n");
   printf("3 - Atividades agrupadas por bicicleta, ordenadas por data\n");
   printf("4 - Atividades agrupadas por bicicleta, ordenadas por distância\n");
   printf("5 - Atividades ordenadas por subida acumulada\n");
   printf("6 - Histograma\n");
   printf("7 - Sair\n");
}

/*imprime uma linha para separar as informacoes*/
void imprimeSeparador(){
   printf("\n");
   for(int i = 0; i < 119; i++){
      printf("-");
   }
}

/*imprime infos gerais de uma bike*/
int imprimeInfos(t_Bike *aux){
   printf("\n");
   printf("\n");
   printf("\tQtd. Atividades     Total Percorrido     Pedal mais curto     ");
   printf("Pedal mais longo     Distancia média\n");
   printf("\t\t\t\t(km)\t\t      (km)");
   printf("\t\t   (km) \t\t(km)\n");
   printf("\t %d", aux->tam);
   printf("\t\t\t%6.2f", aux->distT);
   printf("\t\t    %6.2f ", aux->pedalC);
   printf("\t\t %6.2f ", aux->pedalL);
   printf("\t       %6.2f \n", aux->distT/aux->tam);

   return 0;
}

/*imprime cabecalho das informacoes*/
void imprimirCabecalho(){
   printf("\n");
   printf("\t Distância   Velocidade Média   Velocidade Máxima   ");
   printf("HR Médio   HR Máximo   Cadência Média   Subida Acumulada\n");
   printf("Data\t (km)\t\t (km/h)\t\t   (km/h)");
   printf("\t     (bpm)\t  (bpm)\t\t(rpm)\t\t(metros)\n");
   printf("\n");
}

/*imprime informações de uma atividade*/
void imprimirLog(t_LogBike vet[], int i){
   printf("%02d/%02d ", vet[i].Dia, vet[i].Mes);
   printf("\t %6.2f ", vet[i].Distancia);
   printf("\t %6.2f ", vet[i].VelocidadeMed);
   printf("\t   %6.2f ", vet[i].VelocidadeMax);
   printf("\t     %6.0f \t\t", vet[i].HRmedio);
   printf("%d ", vet[i].HRmax);
   printf("\t\t  %.0f ", vet[i].Cadencia);
   printf("\t\t%6.2f\n", vet[i].SubidaAcum);
}

/*imprime registros de apenas do modelo passado, sem ordenacao*/
void imprimirModelo(t_LogBike vet[], int tam){
	for(int i = 0; i < tam; i++){
		imprimirLog(vet, i);
   }
}

/*retorna a diferenca da distancia de a com a de b*/
int compara_dist(const void *a, const void *b){
   t_LogBike *logA = (t_LogBike *)a;
   t_LogBike *logB = (t_LogBike *)b;

   return (int)(logA->Distancia - logB->Distancia);
}

/*retorna a diferenca da subda de a com a de b*/
int compara_subida(const void *a, const void *b){
   t_LogBike *logA = (t_LogBike *)a;
   t_LogBike *logB = (t_LogBike *)b;

   return (int)(logA->SubidaAcum - logB->SubidaAcum);
}

/*compara duas datas e retorna -1 caso a data de b seja antes da de a,
 1 caso a data de a seja depois da de b, ou zero caso sejam iguais*/
int compara_data(const void *a, const void *b){
   t_LogBike *logA = (t_LogBike *)a;
   t_LogBike *logB = (t_LogBike *)b;

   if((logA->Mes > logB->Mes) || ((logA->Mes == logB->Mes) && (logA->Dia > logB->Dia))){
      return 1;
   }
   else if((logB->Mes > logA->Mes) || ((logB->Mes == logA->Mes) && (logB->Dia > logA->Dia))){
      return -1;
   }
   return 0;
}

/*ordena por distancia e depois imprime as atividades*/
void imprimirDist(t_LogBike vet[], int tam){
   qsort(vet, tam, sizeof(t_LogBike), compara_dist);
	imprimirModelo(vet, tam);
}

/*ordena por data e depois imprime as atividades*/
void imprimirData(t_LogBike vet[], int tam){
	qsort(vet, tam, sizeof(t_LogBike), compara_data);
	imprimirModelo(vet, tam);
}

/*ordena por subida acumulada e depois imprime as atividades*/
void imprimirSubida(t_LogBike vet[], int tam){
	qsort(vet, tam, sizeof(t_LogBike), compara_subida);
	imprimirModelo(vet, tam);
}

/*arredonda um double para o multiplo de 10 mais próximo*/
int arredonda10(double x){
	int r = x/10;
	return r*10;
}

/*recebe pedal mais longo e mais curto, acha numero de colunas e cria um vetor contando o numero de atividades
naquele intervalo de distancia*/
int histograma(t_ListaBike *lista, double pedalCurto, double pedalLongo){
   FILE *arq;
   int pcurto = arredonda10(pedalCurto);
   int colMax = pedalLongo/10;
   int colMin = pedalCurto/10;
   int col[colMax-colMin+1];
   int pos;

	/*zera vetor contador*/
   for(int i = 0; i < colMax-colMin+1; i++){
      col[i] = 0;
   }

	/*trunca primeiros digitos de um valor para uma posição e aumenta contador da mesma*/
   for(t_Bike *aux = lista->ini; aux != NULL; aux = aux->prox){
      for(int j = 0; j < aux->tam; j++){
         pos = (aux->VetorLog[j].Distancia/10);
         col[pos-(pcurto/10)]++;
      }
   }

	/*cria arquivo hist.dat e salva os dados do vetor contador*/
   arq = fopen("hist.gp", "w");
   if(!arq){
      perror("Erro ao criar arquivo de histograma");
      exit(1);
   }

	fprintf(arq, "$dados << EOD\n");

	/*salva uma coluna com o dezena mais proxima do pedal curto e outra com a quantidade de valores naquela faixa*/
   for(int i = 0; i < colMax-colMin+1; i++){
      fprintf(arq, "%d-%d\t %d\n", i*10+pcurto, i*10+9+pcurto, col[i]);
   }

	fprintf(arq, "EOD\n");

	/*escreve as configuracoes do grafico*/
	fprintf(arq, "set style fill solid noborder\n");
	fprintf(arq, "set offset 0,1,0.5,0.5\n");
	fprintf(arq, "set xrange [0:*]\n");
	fprintf(arq, "set yrange [*:*] reverse\n");
   fprintf(arq, "set xlabel \"Qtd. de Atividades\"\n");
   fprintf(arq, "set ylabel \"Distância em km\"\n");
	fprintf(arq, "set title \"Distâncias das Atividades em km\" \n");
	fprintf(arq, "\n");

   /*eixo x aumenta de 5 em 5 com limite no fim da coluna 2, tamanho das barras eh 0.4, 
   mostra nomes da coluna 1 no eixo y, estilo boxxyerrorbars, com os dados em linhas e não colunas*/
	fprintf(arq, "plot $dados using ($2*0.5):0:($2*0.5):(0.4):yticlabel(1) with boxxyerrorbars notitle\n");

   fclose(arq);

	/*chamada do sistema para o plotar o grafico*/
	return (system("gnuplot -p hist.gp") == -1);
}

/*imprime todos os modelos de bicicleta encontrados*/
int opcao1(t_ListaBike *lista){
   t_Bike *aux = lista->ini;

   printf("\n");
   while(aux != NULL){
      printf("%s\n", aux->Modelo);
      aux = aux->prox;
   }

   return 0;
}

/*busca por uma bicicleta no vetor*/
int opcao2(t_ListaBike *lista){
   t_Bike *aux = lista->ini;
   int i = 0;
   int j = 0;
   int num = 0;

   printf("\n");
   while(aux != NULL){
      printf("%d - %s\n", i, aux->Modelo);
      i++;
      aux = aux->prox;
   }
   /*Le \n para limpar a entrada para o fgets e remove \n no final do fgets*/
   getchar();
   printf("Digite o número da bike desejada: ");
   scanf("%d", &num);

   /*num invalido*/
   if((num > i) || (num < 0)){
      printf("Bicicleta nao encontrada\n");
   }
   /*percorre lista ate achar bike*/
   else{
      aux = lista->ini;
      while(j != num){
         aux = aux->prox;
         j++;
      }
      printf("\n\nBicicleta: %s\n", aux->Modelo);
      imprimirCabecalho();
      imprimirModelo(aux->VetorLog, aux->tam);
      imprimeInfos(aux);
      imprimeSeparador();
   }

   return 0;
}

int opcao3(t_ListaBike *lista){
   for(t_Bike *aux = lista->ini; aux != NULL; aux = aux->prox){
      printf("Bicicleta: %s\n", aux->Modelo);
      imprimirCabecalho();
      imprimirData(aux->VetorLog, aux->tam);
      imprimeInfos(aux);
      imprimeSeparador();
   }

   return 0;
}

int opcao4(t_ListaBike *lista){
   for(t_Bike *aux = lista->ini; aux != NULL; aux = aux->prox){
      printf("Bicicleta: %s\n", aux->Modelo);
      imprimirCabecalho();
      imprimirDist(aux->VetorLog, aux->tam);
      imprimeInfos(aux);
      imprimeSeparador();
   }

   return 0;
}

/*copia todos os logs para um vetor auxiliar e depois o ordena*/
int opcao5(t_ListaBike *lista, int numlog){
   t_LogBike vetLog[numlog];
   int pos = 0;

   /*copia valores do vetor passado para um vetor local*/
   for(t_Bike *aux = lista->ini; aux != NULL; aux = aux->prox){
      for(int j = 0; j < aux->tam; j++){
         memcpy(&vetLog[pos], &aux->VetorLog[j], sizeof(t_LogBike));
         pos++;
      }
   }
   imprimirSubida(vetLog, pos);
   imprimeSeparador();

   return 0;
}

int opcao6(t_ListaBike *lista){
   double pedalCurto = lista->ini->pedalC;
   double pedalLongo = lista->ini->pedalL;

   for(t_Bike *aux = lista->ini->prox; aux != NULL; aux = aux->prox){
      if(aux->pedalC < pedalCurto){
         pedalCurto = aux->pedalC;
      }
      else if(aux->pedalL > pedalLongo){
         pedalLongo = aux->pedalL;
      }
   }
   return histograma(lista, pedalCurto, pedalLongo);
}
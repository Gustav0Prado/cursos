//Gustavo do Prado Silva - 20203942 
//Rafael Gonçalves dos Santos - 20211798

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <likwid.h>

#include "sistema.h"
#include "utils.h"
#include "oper.h"
#include "metodos.h"

int main(int argc, char **argv){
   
   LIKWID_MARKER_INIT;

   int opt;
   int n, k, p, it;
   double e = -1;
   char *saida;
   FILE *arq, *fdone, *arqTempo;
   
   double tempMed = 0.0;
   double tempR   = 0.0;
   double tempPC  = 0.0;

   SistLinear_t *SL;

   // Inicializa semente 
   srand(20222);

   // Algum argumento obrigatorio faltando, escreve na saida de erro 
   if( ((argc-1)/2) < 5 ){
      fprintf(stderr, "Argumentos Obrigatórios Faltando!!\n");
      return -1;
   }
   else{
      // usa getopt para pegar valores da entrada 
      while((opt = getopt(argc, argv, "n:k:p:i:e:o:")) != -1){
         //colocar em funcao
         switch(opt){
            case 'n':
               n = atoi(optarg);
               if(n <= 10){
                  fprintf(stderr, "ERRO: Tamanho do sistema linear precisa ser maior que 10\n");
                  return ERRINPUT;
               }
               break;
            case 'k':
               k = atoi(optarg);
               if(k <= 1 || (k % 2 == 0)){
                  fprintf(stderr, "ERRO: k precisa ser maior que 1 e ímpar\n");
                  return ERRINPUT;
               }
               break;
            case 'p':
               p = atoi(optarg);
               if(p < 0){
                  fprintf(stderr, "ERRO: Identificador do Pré-Condicionador precisa ser maior ou igual a 0\n");
                  return ERRINPUT;
               }
               break;
            case 'i':
               it = atoi(optarg);
               if(it < 1){
                  fprintf(stderr, "ERRO: Número de iterações precisa ser maior que 0\n");
                  return ERRINPUT;
               }
               break;
            case 'e':
               e = atof(optarg);
               if(e < 0.0){
                  fprintf(stderr, "ERRO: Valor do erro precisa ser maior ou igual a 0.0\n");
                  return ERRINPUT;
               }
               break;
            case 'o':
               saida = optarg;
               break;
            default:
               fprintf(stderr, "Opcao invalida ou faltando argumento: `%c'\n", optopt) ;
               return ERRINPUT;
               break;
         }
      }
   }

   if(k > n){
      fprintf(stderr, "Erro! Numero de diagonais não pode ser maior que o tamanho da matriz\n") ;
      return ERRINPUT;
   }

   SL = alocaSisLin (n);
   SistLinear_t* SLorig = alocaSisLin (n);

   if(!SL){
      fprintf(stderr, "Erro de alocação!\n");
      exit(ERRALLOC);
   }

   // gera os coeficientes da matriz
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         //zera elementos que nao estao nas diagonais
         int banda = (k-1)/2;
         if( j > i+banda || j < i-banda ){
            SL -> A[i][j] = 0.0;
         }
         else{
            SL -> A[i][j] = generateRandomA (i, j, k);
         }
      }
      SL -> b[i] = generateRandomB (k);
   }
   SL->i = it;

   //copia sistema original
   memcpy(SLorig->b, SL->b, sizeof(double)*n);
   for(int i = 0; i < n; ++i){
      memcpy(SLorig->A[i], SL->A[i], sizeof(double)*n);
   }
   SLorig->n = SL->n;

   //vetores do residuo e x inicial e matrix pre-condicionadora
   double *r   = malloc(sizeof(double)*n);
   double *x   = malloc(sizeof(double)*n);
   double **M  = malloc(sizeof(double*)*n);

   //checa erros de alocação
   if(!r || !x || !M){
      fprintf(stderr, "Erro de alocação!\n");
      exit(ERRALLOC);
   }

   //inicializa x = 0
   memset(x, 0, SL->n*sizeof(*x));
   
   // se p = 0, M = I
   // se p > 0, M = D
   tempPC = timestamp();

   simetrizaSistema (SL);

   if(p == 0){
      //cria matriz identidade; I^(-1) = I, diagonais = 1
      for(int i = 0; i < n; ++i){
         M[i] = malloc(sizeof(double)*n);
         if(!M[i]){
            fprintf(stderr, "Erro de alocação!\n");
            exit(ERRALLOC);
         }
         memset(M[i], 0, n*sizeof(double));
         M[i][i] = 1.0;
      }
   }
   else{
      //cria matriz diagonal; D^(-1) 
      for(int i = 0; i < n; ++i){
         M[i] = malloc(sizeof(double)*n);
         if(!M[i]){
            fprintf(stderr, "Erro de alocação!\n");
            exit(ERRALLOC);
         }
         memset(M[i], 0, n*sizeof(double));
         M[i][i] = SL->A[i][i] * (1 / (SL->A[i][i] * SL->A[i][i]));
      }
   }
   tempPC = timestamp() - tempPC;

   //abre arquivo para escrita
   arq = fopen(saida, "w");
   if(!arq){
      fprintf(stderr, "Erro ao criar arquivo de saída!\n");
      return ERROUTPUT;
   }

   fprintf(arq, "# gps20 Gustavo do Prado\n");
   fprintf(arq, "# rgs21 Rafael Gonçalves\n");
   fprintf(arq, "#\n");

   double tempoOp1 = timestamp();

   LIKWID_MARKER_REGISTER("op1-v1");
   LIKWID_MARKER_START("op1-v1");

   //sem erro definido, apenas faz iteracoes
   if(e == -1){
      tempMed = GradConjIt(SL, x, M, arq);
   }
   //com erro definido
   else{
      tempMed = GradConjErr(SL, x, M, e, arq);
   }

   LIKWID_MARKER_STOP("op1-v1");

   tempoOp1 = timestamp() - tempoOp1;

   double tempoOp2 = timestamp();

   LIKWID_MARKER_REGISTER("op2-v1");
   LIKWID_MARKER_START("op2-v1");

   //calcula residuo final
   somaVetMatxVet(SLorig->A, SLorig->b, x, -1, r, n);

   LIKWID_MARKER_STOP("op2-v1");

   tempoOp2 = timestamp() - tempoOp2;


   //Escreve no arquivo com tempos
   //abre arquivo com os tempos para escrita
   char diretorio[256];
   char done[256];
   getcwd(diretorio, sizeof(diretorio));
   strncpy(done, diretorio, 256);

   strcat(diretorio, "/saida/plot_Tempo-v2.dat");
   strcat(done, "/saida/done-v2");

   /* checa se arquivo "done" ja existe, se sim entao o loop foi rodado uma vez
      se nao coloca as informacoes de tempo em modo append, assim pega os tempos apenas uma vez
   */
   if((fdone = fopen(done, "r")) == NULL){   
      arqTempo = fopen(diretorio, "a");
      if(!arqTempo){
         fprintf(stderr, "Erro ao criar arquivo com tempos!\n");
         return ERROUTPUT;
      }
      fprintf(arqTempo, "%d %.5g %.5g\n", n, tempoOp1, tempoOp2);
      fclose(arqTempo);
   }

   fprintf(arq, "# residuo: %.15g\n", normaL2(r, n, &tempR));
   fprintf(arq, "# Tempo PC: %.15g\n", tempPC);
   fprintf(arq, "# Tempo iter: %.15g\n", tempMed);
   fprintf(arq, "# Tempo residuo: %.15g\n", tempR);
   fprintf(arq, "#\n");
   fprintf(arq, "%d\n", n);

   //imprime solucao final
   for(int j = 0; j < n; ++j){
      fprintf(arq, "%.15g ", x[j]);
   }
   fprintf(arq, "\n");

   //fecha arquivo de saida
   fclose(arq);

   //libera estruturas
   free(x);
   free(r);
   for (int i = 0; i < n; i++){
      free (M[i]);
   }
   free (M);
   liberaSisLin (SL);

   LIKWID_MARKER_CLOSE;

   return 0;
}
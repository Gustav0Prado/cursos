#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "sistema.h"
#include "utils.h"
#include "oper.h"
#include "metodos.h"

int main(int argc, char **argv){
   int opt;
   int n, k, p, it;
   double e = -1;
   char *saida;

   SistLinear_t *SL;

   // Inicializa semente 
   srand(20222);

   /* Algum argumento obrigatorio faltando, escreve na saida de erro */
   if( ((argc-1)/2) < 5 ){
      fprintf(stderr, "Argumentos Obrigatórios Faltando!!\n");
      return -1;
   }
   else{
      /* usa getopt para pegar valores da entrada */
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
               return -1;
               break;
         }
      }
   }

   SL = alocaSisLin (n);
   // gera os coeficientes da matriz
   for (int i = 0; i < n; i++) {
      for (int j = 0; j <= i; j++) {
         //zera elementos que nao estao nas diagonais
         int banda = (k-1)/2;
         if( j > i+banda || j < i-banda ){
            SL -> A[i][j] = 0.0;
         }
         else{
            SL -> A[i][j] = generateRandomA (i, j, k);
            //simetria na matriz
            SL -> A[j][i] = SL -> A[i][j];
         }
      }
      SL -> b[i] = generateRandomB (k);
   }

   // /* SL = lerSisLin (); */
   prnSisLin (SL);

   SL->i = it;

   double *r   = malloc(sizeof(double)*n);
   double *x   = malloc(sizeof(double)*n);
   double **M  = malloc(sizeof(double*)*n);

   //inicializa x = 0
   memset(x, 0, SL->n*sizeof(*x));

   //colocar metodos numericos em funcoes, uma com erro e uma sem
   // se p = 0, M = I
   // se p > 0, M = D
   if(p == 0){
      //cria matriz identidade; I^(-1) = I, diagonais = 1
      for(int i = 0; i < n; ++i){
         M[i] = malloc(sizeof(double)*n);
         memset(M[i], 0, n*sizeof(double));
         M[i][i] = 1.0;
      }
   }
   else{
      //cria matriz M = D
   }

   double tempMed = 0.0;

   //sem erro definido, apenas faz iteracoes
   if(e == -1){
      tempMed = GradConjIt(SL, x, M);
   }
   //com erro definido
   else{
      tempMed = GradConjErr(SL, x, M, e);
   }

   printf("Tempo médio das iterações: %15g\n", tempMed);

   //imprime solucao final
   for(int j = 0; j < n; ++j){
      printf("%g ", x[j]);
   }
   printf("\n");

   free(x);
   free(r);

   liberaSisLin (SL);

   return 0;
}
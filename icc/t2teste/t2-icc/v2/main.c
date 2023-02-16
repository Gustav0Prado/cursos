//Gustavo do Prado Silva - 20203942 
//Rafael Gonçalves dos Santos - 20211798

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
   FILE *arq;
   
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
               if(n <= 3){
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
   //SL = alocaSisLin (n, k);
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

   //prnSisLin(SL);

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

   //sem erro definido, apenas faz iteracoes
   if(e == -1){
      tempMed = GradConjIt(SL, x, M, arq);
   }
   //com erro definido
   else{
      tempMed = GradConjErr(SL, x, M, e, arq);
   }

   //prnSisLin(SL);

   //calcula residuo final
   somaVetMatxVet(SLorig->A, SLorig->b, x, -1, r, n);

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



   //Teste com matrizes
   // Matriz como vetor de N ponteiros para um único vetor com N*N elementos
   double **A = malloc(n * sizeof(double *));
   double **B = malloc(k * sizeof(double *));
   double **D = malloc(n * sizeof(double *));
   int tam = ((n-k+1)*k) + ((k-1)*(k))/2;

   A[0] = (double *) malloc( n*k * sizeof(double));
   B[0] = (double *) malloc( n*k * sizeof(double));
   D[0] = (double *) malloc( tam * sizeof(double));


   for (int i=1; i < n; ++i) {

      A[i] = A[i-1]+k;
      memset(A[i],  0, k*sizeof(double));
   }

   for (int i=1; i < k; ++i) {
      B[i] = B[i-1]+n;
      memset(B[i],  0, n*sizeof(double));
   }

   for (int i=1; i <= n-k+1; ++i) {
      D[i] = D[i-1]+k;
      memset(D[i],  0, k*sizeof(double));
   }

   for (int i = n-k+2; i < n; ++i) {
      D[i] = D[i-1]+(n-i+1);
      memset(D[i],  0, (n-i)*sizeof(double));
   }

   memset(A[0],  0, k*sizeof(double));
   memset(D[0],  0, k*sizeof(double));

   int jstart[n];
   int jend[n];
   int start = 1;
   
   /* Salva inicio e final de cada diagonal */
   for(int i = 0; i <= k/2; ++i){
      jstart[i] = 0;
      jend[i] = k-1;
   }
   for(int i = (k/2)+1; i < n-(k/2); ++i){
      //jstart[i] = start;
      jstart[i] = i-(k/2);
      jend[i] = jstart[i]+k-1;
      ++start;
   }
   for(int i = n-(k/2); i < n ;++i){
      jstart[i] = i-(k/2);
      jend[i] = n-1;
   }

   /* Cria matriz n*k com as diagonais */
   for(int i = 0; i < n; ++i){
      //printf("%d, %d\n", jstart[i], jend[i]);

      int m = 0;
      for(int j = jstart[i]; j <= jend[i]; ++j){
         A[i][m] = SLorig->A[i][j];
         ++m;
      }
   }

   for(int i = 0; i < n; ++i){
      for(int j = 0; j < k; ++j){
         printf("%10g ", A[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   /* Cria matriz k*n transposta */
   for(int i = 0; i < k; ++i){
      for(int j = 0; j < n; ++j){
         B[i][j] = A[j][i];
      }
   }

   for(int i = 0; i < k; ++i){
      for(int j = 0; j < n; ++j){
         printf("%10g ", B[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   /* Cria matriz simetrica, com apenas diagonais da principal para cima */
   for(int i = 0; i < n; ++i){
      //calcula diagonal principal
      for(int j = 0; j < n-i; ++j){
         D[j][i];
         int m = jstart[j+i]-jstart[j];
         int l = 0;
         
         while(m < k){
            D[j][i] += A[j][m] * B[l][j+i];
            ++m;
            ++l;
         }
      }
   }

   /* Teste de mult com vetor */
   double vet[n];
   double vetResSim[n];

   for(int i = 0; i < n; ++i){
      vet[i] = i+1;
      vetResSim[i] = 0.0;
      printf("%g ", vet[i]);
   }
   printf("\n\n");

   int simjstart[n];
   int simjend[n];
   start = 1;
   
   /* Salva inicio e final de cada linha */
   for(int i = 0; i <= n-k; ++i){
      simjstart[i] = i;
      simjend[i] = k+i-1;
      //printf("%d,%d\n", simjstart[i], simjend[i]);
   }
   for(int i = n-k+1; i < n; ++i){
      simjstart[i] = i;
      simjend[i] = n-1;
      //printf("%d,%d\n", simjstart[i], simjend[i]);
   }

   /* linhas com tamanho k */
   for (int i = 0; i <= n-k; ++i) {
      for(int j = 0; j < k; ++j){
         printf("%10g ", D[i][j]);
      }
      printf("\n");
   }

   /* linhas comecam a diminuir */
   for (int i = n-k+1; i < n; ++i) {
      for(int j = 0; j < n-i; ++j){
         printf("%10g ", D[i][j]);
      }
      printf("\n");
   }

   printf("\n");

   /* multiplica com vetor */
   for (int i = 0; i < n; ++i) {
      int maxj = simjend[i]-simjstart[i]+1;
      for(int j = 0; j < maxj; ++j){
         //printf("%10g += %10g * %2g\n", vetRes[i], D[i][j], vet[simjstart[i]+j]);
         vetResSim[i] += D[i][j] * vet[simjstart[i]+j];
      }
   }

   /* multiplica valores simetricos com vetor */
   for (int i = 1; i < n; ++i) {
      int ii = i-1;
      int jj = 1;

      while(jj < k && ii >= 0){
         vetResSim[i] += D[ii][jj] * vet[ii];
         ii--;
         jj++;
      }
   }
   printf("\n");

   /* Desaloca estruturas */
   free (A[0]);
   free(A);
   free (B[0]);
   free(B);
   free (D[0]);
   free(D);


   //libera estruturas
   free(x);
   free(r);
   for (int i = 0; i < n; i++){
      free (M[i]);
   }
   free (M);
   liberaSisLin (SL);
   liberaSisLin (SLorig);

   return 0;
}
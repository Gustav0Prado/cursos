#include <stdio.h>
#include <stdlib.h>

int main(){
   int n, m;
   scanf("%d", &n);
   scanf("%d", &m);

   // Alocação dos vetores para guardar os valores
   int *preco  = malloc(sizeof(int) * n);
   double *lucro  = malloc(sizeof(int) * n);
   int *custo   = malloc(sizeof(int) * m);
   int *limite  = malloc(sizeof(int) * m);

   // Matriz n x m com quantidades dos produtos/compostro
   double **mat = malloc(sizeof(double*) * m);
   for(int i = 0; i < m; ++i){
      mat[i] = malloc(sizeof(double*) * n);
   }


   /*
      Lê valores com os preços
   */
   for(int i = 0; i < n; ++i){
      scanf("%d", &(preco[i]));
   }


   /*
      Lê valores de custo e limite de produção
   */
   for(int i = 0; i < m; ++i){
      scanf("%d", &(custo[i]));
      scanf("%d", &(limite[i]));
   }


   /*
      Lê matriz com os coeficientes
   */
   for(int i = 0; i < n; ++i){
      for(int j = 0; j < m; ++j){
         scanf("%lf", &(mat[j][i]));
      }
   }


   /*
      Calcula lucro baseado: preco(x0) - custo(x0)*quantidade(x0)
   */
   for(int i = 0; i < n; ++i){
      double custoTotali = 0.0;
      for(int j = 0; j < m; ++j){
         custoTotali += custo[j] * mat[j][i];
      }
      lucro[i] = preco[i] - custoTotali;
   }


   /*
      Imprime função objetivo, primeiro fora do laço pra não 'sobrar' um sinal de + no inicio
   */
   printf("max: ");
   printf("%gx%d", lucro[0], 0);

   for(int i = 1; i < n; ++i){
      printf(" + %gx%d", lucro[i], i);
   }
   printf(";\n");


   /*
      Imprime matriz de coeficientes já como variaveis para o lp_solve
   */
   for(int i = 0; i < m; ++i){
      printf("%5gx%d", mat[i][0], 0);
      for(int j = 1; j < n; ++j){
         printf("   + %5gx%d", mat[i][j], j);
      }
      printf("  <= %5d;\n", limite[i]);
   }


   /*
      Libera todas as estruturas
   */
   free(preco);
   free(custo);
   free(limite);
   for(int i = 0; i < n; ++i){
      free(mat[i]);
   }
   free(mat);
}

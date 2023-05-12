#include <stdio.h>
#include <stdlib.h>

int main(){
  int n, m;
  scanf("%d", &n);
  scanf("%d", &m);
  
  //Alocação dos vetores para guardar os valores
  int *precos  = malloc(sizeof(int) * n);
  int *custo   = malloc(sizeof(int) * m);
  int *limite  = malloc(sizeof(int) * m);
  
  //Matriz n x m com quantidades dos produtos/compostro
  double **mat = malloc(sizeof(double*) * n);
  for(int i = 0; i < n; ++i){
    mat[i] = malloc(sizeof(double*) * m);
  }

  for(int i = 0; i < n; ++i){
    scanf("%d", &(precos[i]));
  }
  
  for(int i = 0; i < m; ++i){
    scanf("%d", &(custo[i]));
    scanf("%d", &(limite[i]));
  }

  for(int i = 0; i < n; ++i){
    for(int j = 0; j < m; ++j){
      scanf("%lf", &(mat[i][j]));
    }
  }

  free(precos);
  free(custo);
  free(limite);
  for(int i = 0; i < n; ++i){
    free(mat[i]);
  }
  free(mat);
}

// Gustavo do Prado Silva - GRR20203942

#include <stdio.h>
#include <math.h>
#include <string.h>

#include "utils.h"
#include "sislin.h"
#include "Metodos.h"

/*!
  \brief Copia valores de uma matriz para outra

  \param SL Ponteiro para o sistema linear de origem
  \param SL Ponteiro para o sistema linear de destino
*/
void copiaMatriz(SistLinear_t *SLDest, SistLinear_t *SLOrig, int tam)
{
  for(int i = 0; i < tam; i++){
    for(int j = 0; j < tam; j++){
      SLDest->A[i][j] = SLOrig->A[i][j];
    }
    SLDest->b[i] = SLOrig->b[i];
  }
}

int main ()
{
  // inicializa gerador de números aleatóreos
  srand(202202);
  
  int TAM_MATRIZES[6] = {10, 30, 50, 128, 256, 512};

  SistLinear_t *SL;
  SistLinear_t *SLOrig;
  real_t *x;
  double tTotal = 0.0;

  printf("Eliminação de Gauss: \n");
  for(int i = 0; i < 6; i++){
    int tam = TAM_MATRIZES[i];

    SL = alocaSisLin(tam);
    SLOrig = alocaSisLin(tam);
    x = malloc(sizeof(real_t)*tam);

    //if SL -> testa ponteiro
    iniSisLin(SL, diagDominante, 10.0);
    copiaMatriz(SLOrig, SL, tam);

    /* eliminacao de gauss */
    eliminacaoGauss(SLOrig, SL, x, &tTotal);
    printf("Tamanho da Matriz: %4d  Tempo de execução: %10g\n", tam, tTotal);

    /* Desaloca estruturas */
    liberaSisLin(SL);
    liberaSisLin(SLOrig);
    free(x);
  }

  printf("Gauss-Seidel: \n");
  for(int i = 0; i < 6; i++){
    int tam = TAM_MATRIZES[i];

    SL = alocaSisLin(tam);
    SLOrig = alocaSisLin(tam);
    x = malloc(sizeof(real_t)*tam);

    //if SL -> testa ponteiro
    iniSisLin(SL, diagDominante, 10.0);
    copiaMatriz(SLOrig, SL, tam);

    /* eliminacao de gauss */
    int it = gaussSeidel(SL, x, ERRO, &tTotal);
    printf("Tamanho da Matriz: %4d  Tempo de execução: %10g  Iterações: %d\n", tam, tTotal, it);

    /* Desaloca estruturas */
    liberaSisLin(SL);
    liberaSisLin(SLOrig);
    free(x);
  }
}


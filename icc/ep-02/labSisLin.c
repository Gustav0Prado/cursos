// Gustavo do Prado Silva - GRR20203942

/*
  EGP mais rapido que GS em sistemas diagDominante menores??? (10x10)
*/

#include <stdio.h>
#include <math.h>
#include <string.h>

#include "utils.h"
#include "sislin.h"
#include "Metodos.h"

#define QTD_MAT 1
//#define QTD_MAT 6

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
  
  //int TAM_MATRIZES[QTD_MAT] = {10, 30, 50, 128, 256, 512};
  int TAM_MATRIZES[QTD_MAT] = {256};

  SistLinear_t *SL1, *SL2;
  real_t *x1, *x2, *x3;
  double tTotal = 0.0;

  printf("Diagonal Dominante: \n");
  for(int i = 0; i < QTD_MAT; i++){
    int tam = TAM_MATRIZES[i];

    SL1 = alocaSisLin(tam);
    SL2 = alocaSisLin(tam);
    x1 = malloc(sizeof(real_t)*tam);
    x2 = malloc(sizeof(real_t)*tam);
    x3 = malloc(sizeof(real_t)*tam);

    //if SL -> testa ponteiro
    iniSisLin(SL1, generico, 15.0);
    copiaMatriz(SL2, SL1, tam);

    printf("   Tamanho: %d\n", tam);

    /* eliminacao de gauss */
    eliminacaoGauss(SL1, x1, &tTotal);
    printf("   Eliminação Gauss:   %g\n", tTotal);

    /* Gauss-Seidel */
    int itGS = gaussSeidel(SL2, x2, ERRO, &tTotal);
    printf("   Gauss-Seidel:       %g, %2d iteracoes\n", tTotal, itGS);

    /* copia x1 pra x3 */
    for(int i = 0; i < tam; i++){
      x3[i] = x1[i];
    }

    /* refinamento */
    int itR = refinamento(SL2, x3, ERRO, &tTotal);
    printf("   Refinamento:        %g, %2d iteracoes\n", tTotal, itR);
    printf("   -------------------------------------------\n");

    // prnVetor(x1, tam);
    // prnVetor(x2, tam);
    // prnVetor(x3, tam);

    /* Desaloca estruturas */
    liberaSisLin(SL1);
    liberaSisLin(SL2);
    free(x1);
    free(x2);
    free(x3);
  }
}
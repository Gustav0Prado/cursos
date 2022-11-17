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

#define QTD_MAT 6

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
  
  int TAM_MATRIZES[QTD_MAT] = {10, 30, 50, 128, 256, 512};


  SistLinear_t *SL1, *SL2;
  real_t *x1, *x2, *x3;
  double tEGP = 0.0, tGS = tEGP, tREF = tEGP;

  printf("Diagonal Dominante: \n");
  printf("   n   |   t_egp   | normaResiduo_egp |    t_gs    |   it_gs   |");
  printf(" normaResiduo_gs |   t_ref   |   it_ref   | normaResiduo_ref|\n");
  printf("-------------------------------------------------------------");
  printf("--------------------------------------------------------------\n");
  for(int i = 0; i < QTD_MAT; i++){
    int tam = TAM_MATRIZES[i];

    SL1 = alocaSisLin(tam);
    SL2 = alocaSisLin(tam);
    x1 = malloc(sizeof(real_t)*tam);
    x2 = malloc(sizeof(real_t)*tam);
    x3 = malloc(sizeof(real_t)*tam);

    //if SL -> testa ponteiro
    iniSisLin(SL1, diagDominante, 32.0);
    copiaMatriz(SL2, SL1, tam);

    /* eliminacao de gauss */
    eliminacaoGauss(SL1, x1, &tEGP);

    /* Gauss-Seidel */
    int itGS = gaussSeidel(SL2, x2, ERRO, &tGS);

    /* copia x1 pra x3 */
    for(int i = 0; i < tam; i++){
      x3[i] = x1[i];
    }

    /* refinamento */
    int itREF = refinamento(SL2, x3, ERRO, &tREF);

    printf("%4d   |%10g |   %10g     | %10g |   %4d    |   %10g    |", tam, tEGP, 0.015472, tGS, itGS, 0.015472);
    printf("%10g |    %4d    |   %10g     \n", tREF, itREF, 0.015472);

    /* Desaloca estruturas */
    liberaSisLin(SL1);
    liberaSisLin(SL2);
    free(x1);
    free(x2);
    free(x3);
  }

  printf("\n\nGenerica: \n");
  printf("   n   |   t_egp   | normaResiduo_egp |    t_gs    |   it_gs   |");
  printf(" normaResiduo_gs |   t_ref   |   it_ref   | normaResiduo_ref|\n");
  printf("-------------------------------------------------------------");
  printf("--------------------------------------------------------------\n");
  for(int i = 0; i < QTD_MAT; i++){
    int tam = TAM_MATRIZES[i];

    SL1 = alocaSisLin(tam);
    SL2 = alocaSisLin(tam);
    x1 = malloc(sizeof(real_t)*tam);
    x2 = malloc(sizeof(real_t)*tam);
    x3 = malloc(sizeof(real_t)*tam);

    //if SL -> testa ponteiro
    iniSisLin(SL1, generico, 32.0);
    copiaMatriz(SL2, SL1, tam);

    /* eliminacao de gauss */
    eliminacaoGauss(SL1, x1, &tEGP);

    /* Gauss-Seidel */
    int itGS = gaussSeidel(SL2, x2, ERRO, &tGS);

    /* copia x1 pra x3 */
    for(int i = 0; i < tam; i++){
      x3[i] = x1[i];
    }

    /* refinamento */
    int itREF = refinamento(SL2, x3, ERRO, &tREF);

    printf("%4d   |%10g |   %10g     | %10g |   %4d    |   %10g    |", tam, tEGP, 0.015472, tGS, itGS, 0.015472);
    printf("%10g |    %4d    |   %10g     \n", tREF, itREF, 0.015472);

    /* Desaloca estruturas */
    liberaSisLin(SL1);
    liberaSisLin(SL2);
    free(x1);
    free(x2);
    free(x3);
  }

  printf("\n\nHilbert: \n");
  printf("   n   |   t_egp   | normaResiduo_egp |    t_gs    |   it_gs   |");
  printf(" normaResiduo_gs |   t_ref   |   it_ref   | normaResiduo_ref|\n");
  printf("-------------------------------------------------------------");
  printf("--------------------------------------------------------------\n");
  for(int i = 0; i < QTD_MAT; i++){
    int tam = TAM_MATRIZES[i];

    SL1 = alocaSisLin(tam);
    SL2 = alocaSisLin(tam);
    x1 = malloc(sizeof(real_t)*tam);
    x2 = malloc(sizeof(real_t)*tam);
    x3 = malloc(sizeof(real_t)*tam);

    //if SL -> testa ponteiro
    iniSisLin(SL1, hilbert, 32.0);
    copiaMatriz(SL2, SL1, tam);

    /* eliminacao de gauss */
    eliminacaoGauss(SL1, x1, &tEGP);

    /* Gauss-Seidel */
    int itGS = gaussSeidel(SL2, x2, ERRO, &tGS);

    /* copia x1 pra x3 */
    for(int i = 0; i < tam; i++){
      x3[i] = x1[i];
    }

    /* refinamento */
    int itREF = refinamento(SL2, x3, ERRO, &tREF);

    printf("%4d   |%10g |   %10g     | %10g |   %4d    |   %10g    |", tam, tEGP, 0.015472, tGS, itGS, 0.015472);
    printf("%10g |    %4d    |   %10g     \n", tREF, itREF, 0.015472);

    /* Desaloca estruturas */
    liberaSisLin(SL1);
    liberaSisLin(SL2);
    free(x1);
    free(x2);
    free(x3);
  }
}
// Gustavo do Prado Silva - GRR20203942

/*
  EGP mais rapido que GS em sistemas menores???
*/

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

  //SistLinear_t *SL;
  //SistLinear_t *SLOrig;
  SistLinear_t *SL1, *SL2;
  //real_t *x;
  real_t *x1, *x2;
  double tTotal = 0.0;

  printf("Diagonal Dominante: \n");
  for(int i = 0; i < 6; i++){
    int tam = TAM_MATRIZES[i];

    SL1 = alocaSisLin(tam);
    SL2 = alocaSisLin(tam);
    x1 = malloc(sizeof(real_t)*tam);
    x2 = malloc(sizeof(real_t)*tam);

    //if SL -> testa ponteiro
    iniSisLin(SL1, diagDominante, 10.0);
    copiaMatriz(SL2, SL1, tam);

    printf("Tamanho: %d\n", tam);

    /* eliminacao de gauss */
    eliminacaoGauss(SL1, x1, &tTotal);
    printf("Eliminação Gauss:   %g\n", tTotal);

    int it = gaussSeidel(SL2, x2, ERRO, &tTotal);
    printf("Gauss-Seidel:       %g\n", tTotal, it);
    printf("-----------------------------------\n");

    /* comparar vetores x? */
    for(int i = 0; i < tam; i++){
      if(fabs(x1[i] - x2[i]) > ERRO){
        printf("RESULTADOS DIFERENTES!!!!!!!\n");
      }
    }

    /* Desaloca estruturas */
    liberaSisLin(SL1);
    liberaSisLin(SL2);
    free(x1);
    free(x2);
  }
}


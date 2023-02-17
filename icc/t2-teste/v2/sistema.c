//Gustavo do Prado Silva - 20203942 
//Rafael Gonçalves dos Santos - 20211798

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sistema.h"

void liberaSisLin (SistLinear_t *SL)
{
  if (SL) {
    if (SL->Sim.A) {
      if (SL->Sim.A[0]) free (SL->Sim.A[0]);
    free(SL->Sim.A);
    }
    if (SL->Diag.A) {
      if (SL->Diag.A[0]) free (SL->Diag.A[0]);
    free(SL->Diag.A);
    }
    
    if (SL->Sim.b) free(SL->Sim.b);
    if (SL->Diag.b) free(SL->Diag.b);

    if (SL->Sim.jstart) free(SL->Sim.jstart);
    if (SL->Sim.jend) free(SL->Sim.jend);

    if (SL->Diag.jstart) free(SL->Diag.jstart);
    if (SL->Diag.jend) free(SL->Diag.jend);

    free(SL);
  }
}

SistLinear_t* alocaSisLin (unsigned int n, unsigned int k)
{
  SistLinear_t *SL = (SistLinear_t *) malloc(sizeof(SistLinear_t));
  
  if ( SL ) {
    SL->n = n;
    SL->k = k;
    SL->Diag.A = (double **)malloc(n * sizeof(double *));
    SL->Sim.A  = (double **)malloc(n * sizeof(double *));
    SL->Diag.b = (double *) malloc(n * sizeof(double));
    SL->Sim.b  = (double *) malloc(n * sizeof(double));

    if (!(SL->Diag.A) || !(SL->Diag.A) || !(SL->Diag.b) || !(SL->Sim.b)) {
      liberaSisLin(SL);
      fprintf(stderr, "Erro de alocação!\n");
      return NULL;
    }

    // Matriz como vetor de N ponteiros para um único vetor com N*N elementos
    SL->Diag.A[0] = (double *) malloc( n*k * sizeof(double));

    /*  matriz simetrica tem n-k+1 linhas de k elementos, depois cada linha diminui 1
        até chegar no tamanho 1, isso pode ser calculado por uma soma de pa = tamanho(inicial+final) / 2
    */
    int tam = ((n-k+1)*k) + ((k-1)*(k))/2;
    SL->Sim.A[0]  = (double *) malloc( tam * sizeof(double));

    if (!(SL->Diag.A[0]) || !(SL->Sim.A[0])) {
      liberaSisLin(SL);
      fprintf(stderr, "Erro de alocação!\n");
      return NULL;
    }
    
    //Aruma os ponteiros da matriz
    for (int i=1; i < n; ++i) {
      SL->Diag.A[i] = SL->Diag.A[i-1]+k;
      memset(SL->Diag.A[i],  0, k*sizeof(double));
    }

    for (int i=1; i <= n-k+1; ++i) {
      SL->Sim.A[i] = SL->Sim.A[i-1]+k;
      memset(SL->Sim.A[i],  0, k*sizeof(double));
    }

    for (int i = n-k+2; i < n; ++i) {
      SL->Sim.A[i] = SL->Sim.A[i-1]+(n-i+1);
      memset(SL->Sim.A[i],  0, (n-i)*sizeof(double));
    }

    //aloca vetores com posicoes de inicio e final das linhas
    SL->Diag.jstart = (int *) malloc(n * sizeof(int));
    SL->Diag.jend   = (int *) malloc(n * sizeof(int));
    SL->Sim.jstart   = (int *) malloc(n * sizeof(int));
    SL->Sim.jend     = (int *) malloc(n * sizeof(int));

    //zera primeira linha
    memset(SL->Diag.A[0],  0, k*sizeof(double));
    memset(SL->Sim.A[0] ,  0, k*sizeof(double));
    memset(SL->Sim.b ,     0, n*sizeof(double));
  }
  
  return (SL);
}

void prnSisLinDiag (SistLinear_t *SL)
{
  int n=SL->n;
  int k=SL->k;

  for(int i=0; i < n; ++i) {
    for(int j=0; j < k; ++j)
      printf ("%10g", SL->Diag.A[i][j]);
    printf ("   |   %g\n", SL->Diag.b[i]);
  }
  printf("\n\n");
}

void prnSisLinSim (SistLinear_t *SL){
  int n=SL->n;
  int k=SL->k;

  int impar = 2;

  for (int i = 0; i <= n-k; ++i) {
    for(int j = 0; j < k; ++j){
      printf("%10g ", SL->Sim.A[i][j]);
    }
    printf("  |   %g\n", SL->Sim.b[i]);
  }

   /* linhas comecam a diminuir */
   for (int i = n-k+1; i < n; ++i) {
    for(int j = 0; j < n-i; ++j){
      printf("%10g ", SL->Sim.A[i][j]);
    }

    printf("\n");
  }
  printf("\n\n");
}
//Gustavo do Prado Silva - 20203942 
//Rafael Gonçalves dos Santos - 20211798

#include <stdio.h>
#include <stdlib.h>

#include "sistema.h"

void liberaSisLin (SistLinear_t *SL)
{
  if (SL) {
    if (SL->A) {
      if (SL->A[0]) free (SL->A[0]);
    free(SL->A);
    }
    
    if (SL->b) free(SL->b);

    free(SL);
  }
}

SistLinear_t* alocaSisLin (unsigned int n)
{
  SistLinear_t *SL = (SistLinear_t *) malloc(sizeof(SistLinear_t));
  
  if ( SL ) {
    
    SL->n = n;
    SL->A = (double **) malloc(n * sizeof(double *));
    SL->b = (double *) malloc(n * sizeof(double));

    if (!(SL->A) || !(SL->b)) {
      liberaSisLin(SL);
      fprintf(stderr, "Erro de alocação!\n");
      return NULL;
    }

    // Matriz como vetor de N ponteiros para um único vetor com N*N elementos
    SL->A[0] = (double *) malloc(n * n * sizeof(double));
    if (!(SL->A[0])) {
      liberaSisLin(SL);
      fprintf(stderr, "Erro de alocação!\n");
      return NULL;
    }
    
    for (int i=1; i < n; ++i) {
      SL->A[i] = SL->A[i-1]+n;
    }
  }
  
  return (SL);
}

// SistLinear_t* alocaSisLin (unsigned int n, unsigned int k)
// {
//   SistLinear_t *SL = (SistLinear_t *) malloc(sizeof(SistLinear_t));
  
//   if ( SL ) {
//     SL->n = n;
//     SL->Diag.A =(double **)malloc(n * sizeof(double *));
//     SL->Sim.A = (double **)malloc(n * sizeof(double *));
//     SL->Diag.b = (double *) malloc(n * sizeof(double));
//     SL->Sim.b = (double *) malloc(n * sizeof(double));

//     if (!(SL->Diag.A) || !(SL->Diag.A) || !(SL->Diag.b) || !(SL->Sim.b)) {
//       liberaSisLin(SL);
//       fprintf(stderr, "Erro de alocação!\n");
//       return NULL;
//     }

//     // Matriz como vetor de N ponteiros para um único vetor com N*N elementos
//     SL->Diag.A[0] = (double *) malloc( n*k * sizeof(double));

//     /*  matriz simetrica tem n-k+1 linhas de k elementos, depois cada linha diminui 1
//         até chegar no tamanho 1, isso pode ser calculado por uma soma de pa = tamanho(inicial+final) / 2
//     */
//     int tam = ((n-k+1)*k) + ((k-1)*(k))/2;
//     SL->Sim.A[0]  = (double *) malloc( tam * sizeof(double));

//     memset(SL->Diag.A[0],  0, k*sizeof(double));
//     memset(SL->Sim.A[0] ,  0, k*sizeof(double));

//     if (!(SL->Diag.A[0]) || !(SL->Sim.A[0])) {
//       liberaSisLin(SL);
//       fprintf(stderr, "Erro de alocação!\n");
//       return NULL;
//     }
    
//     //Aruma os ponteiros da matriz
//     for (int i=1; i < n; ++i) {
//       SL->Diag.A[i] = SL->Diag.A[i-1]+k;
//       memset(SL->Diag.A[i],  0, k*sizeof(double));
//     }

//     for (int i=1; i <= n-k+1; ++i) {
//       SL->Sim.A[i] = SL->Sim.A[i-1]+k;
//       memset(SL->Sim.A[i],  0, k*sizeof(double));
//     }

//     for (int i = n-k+2; i < n; ++i) {
//       SL->Sim.A[i] = SL->Sim.A[i-1]+(n-i+1);
//       memset(SL->Sim.A[i],  0, (n-i)*sizeof(double));
//     }

//     //aloca vetores com posicoes de inicio e final das linhas
//     SL->Diag.diagjStart = (double *) malloc(n * sizeof(double));
//     SL->Diag.diagjEnd   = (double *) malloc(n * sizeof(double));
//     SL->Sim.simjStart   = (double *) malloc(n * sizeof(double));
//     SL->Sim.simjEnd     = (double *) malloc(n * sizeof(double));
//   }
  
//   return (SL);
// }

void prnSisLin (SistLinear_t *SL)
{
  int n=SL->n;

  for(int i=0; i < n; ++i) {
    printf("\n  ");
    for(int j=0; j < n; ++j)
      printf ("%10g", SL->A[i][j]);
    printf ("   |   %g", SL->b[i]);
  }
  printf("\n\n");
}
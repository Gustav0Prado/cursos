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
      return NULL;
    }

    // Matriz como vetor de N ponteiros para um único vetor com N*N elementos
    SL->A[0] = (double *) malloc(n * n * sizeof(double));
    if (!(SL->A[0])) {
      liberaSisLin(SL);
      return NULL;
    }
    
    for (int i=1; i < n; ++i) {
      SL->A[i] = SL->A[i-1]+n;
    }
  }
  
  return (SL);
}

SistLinear_t *lerSisLin ()
{
  unsigned int n;
  SistLinear_t *SL;
  
  scanf("%d",&n);

  SL = alocaSisLin (n);
  
  for(int i=0; i < n; ++i)
    for(int j=0; j < n; ++j)
      scanf ("%lg", &SL->A[i][j]);

  for(int i=0; i < n; ++i)
    scanf ("%lg", &SL->b[i]);
  
  return SL;
}

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
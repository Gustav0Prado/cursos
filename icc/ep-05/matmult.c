#include <stdio.h>
#include <stdlib.h>    /* exit, malloc, calloc, etc. */
#include <string.h>
#include <getopt.h>    /* getopt */
#include <time.h>
#include <likwid.h>

#include "matriz.h"

int vetIgual(Vetor a, Vetor b, int n){
  for(int i = 0; i < n; ++i){
    if(ABS(a[i]-b[i] > 1e-10)){
      printf("%e\n", a[i]-b[i]);
      return 0;
    }
  }

  return 1;
}

int matIgual(MatRow a, MatRow b, int n, int m){
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < m; ++j){
      if(a[i*n+j] != b[i*n+j]){
        printf("%g -- %g\n", a[i*n+j], b[i*n+j]);
        return 0;
      }
    }
  }

  return 1;
}

/**
 * Exibe mensagem de erro indicando forma de uso do programa e termina
 * o programa.
 */

static void usage(char *progname)
{
  fprintf(stderr, "Forma de uso: %s [ -n <ordem> ] \n", progname);
  exit(1);
}



/**
 * Programa principal
 * Forma de uso: matmult [ -n <ordem> ]
 * -n <ordem>: ordem da matriz quadrada e dos vetores
 *
 */

int main (int argc, char *argv[]) 
{
  int c, n=DEF_SIZE;
  
  MatRow mRow_1, mRow_2, resMat, resMat2;
  Vetor vet, res, res2;
  
  LIKWID_MARKER_INIT;

  /* =============== TRATAMENTO DE LINHA DE COMANDO =============== */

  char *opts = "n:";
  c = getopt (argc, argv, opts);
  
  while ( c != -1 ) {
    switch (c) {
    case 'n':  n = atoi(optarg);              break;
    default:   usage(argv[0]);
    }
      
    c = getopt (argc, argv, opts);
  }
  
  /* ================ FIM DO TRATAMENTO DE LINHA DE COMANDO ========= */
 
  // srand(time(NULL));
  srandom(20212);
      
  res = (real_t *) calloc (n, sizeof(real_t));
  res2 = (real_t *) calloc (n, sizeof(real_t));
  resMat = geraMatRow(n, n, 1);
  resMat2 = geraMatRow(n, n, 1);
    
  mRow_1 = geraMatRow (n, n, 0);
  mRow_2 = geraMatRow (n, n, 0);

  vet = geraVetor (n, 0);

#ifdef DEBUG
    prnMat (mRow_1, n, n);
    prnMat (mRow_2, n, n);
    prnVetor (vet, n);
    printf ("=================================\n\n");
#endif /* DEBUG */

  multMatVet (mRow_1, vet, n, n, res);
    
  multMatRowVet (mRow_1, vet, n, n, res2);

  multMatMat (mRow_1, mRow_2, n, resMat);

  multMatMatRow (mRow_1, mRow_2, n, resMat2);
  
  if(!vetIgual(res, res2, n)){
    fprintf(stderr, "ERRO! Resultados dos vetores diferentes!\n");
  }
  else if( !matIgual(resMat, resMat2, n, n)){
    fprintf(stderr, "ERRO! Resultados dos vetores diferentes!\n");
  }

#ifdef DEBUG
    prnVetor (res, n);
    prnVetor (res2, n);
    prnMat (resMat, n, n);
    prnMat (resMat2, n, n);
#endif /* DEBUG */

  liberaVetor ((void*) mRow_1);
  liberaVetor ((void*) mRow_2);
  liberaVetor ((void*) resMat);
  liberaVetor ((void*) vet);
  liberaVetor ((void*) res);
  liberaVetor ((void*) res2);

  LIKWID_MARKER_CLOSE;

  return 0;
}


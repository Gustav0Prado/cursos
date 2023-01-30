#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <likwid.h>

#include "matriz.h"

/**
 * Função que gera valores para para ser usado em uma matriz
 * @param i,j coordenadas do elemento a ser calculado (0<=i,j<n)
*  @return valor gerado para a posição i,j
  */
static inline real_t generateRandomA( unsigned int i, unsigned int j)
{
  static real_t invRandMax = 1.0 / (real_t)RAND_MAX;
  return ( (i==j) ? (real_t)(BASE<<1) : 1.0 )  * (real_t)random() * invRandMax;
}

/**
 * Função que gera valores aleatórios para ser usado em um vetor
 * @return valor gerado
 *
 */
static inline real_t generateRandomB( )
{
  static real_t invRandMax = 1.0 / (real_t)RAND_MAX;
  return (real_t)(BASE<<2) * (real_t)random() * invRandMax;
}



/* ----------- FUNÇÕES ---------------- */

/**
 *  Funcao geraMatRow: gera matriz como vetor único, 'row-oriented'
 * 
 *  @param m     número de linhas da matriz
 *  @param n     número de colunas da matriz
 *  @param zerar se 0, matriz  tem valores aleatórios, caso contrário,
 *               matriz tem valores todos nulos
 *  @return  ponteiro para a matriz gerada
 *
 */

MatRow geraMatRow (int m, int n, int zerar)
{
  MatRow matriz = (real_t *) malloc(m*n*sizeof(real_t));

  if (matriz) {
    for (int i=0; i < m; ++i) {
      for (int j=0; j < n; ++j) {
	if (zerar) matriz[i*n + j] = 0.0;
        else       matriz[i*n + j] = generateRandomA(i, j);
      }
    }
  }
  
  return (matriz);
}


/**
 *  Funcao geraVetor: gera vetor de tamanho 'n'
 * 
 *  @param n  número de elementos do vetor
 *  @param zerar se 0, vetor  tem valores aleatórios, caso contrário,
 *               vetor tem valores todos nulos
 *  @return  ponteiro para vetor gerado
 *
 */

Vetor geraVetor (int n, int zerar)
{
  Vetor vetor = (real_t *) malloc(n*sizeof(real_t));

  if (vetor)
    for (int i=0; i < n; ++i) {
      if (zerar) vetor[i] = 0.0;
      else       vetor[i] = generateRandomB();
    }
  
  return (vetor);
}

/**
 *  \brief: libera vetor
 * 
 *  @param  ponteiro para vetor
 *
 */
void liberaVetor (void *vet)
{
	free(vet);
}


/**
 *  Funcao multMatVet:  Efetua multiplicacao entre matriz 'mxn' por vetor
 *                       de 'n' elementos
 *  @param mat matriz 'mxn'
 *  @param m número de linhas da matriz
 *  @param n número de colunas da matriz
 *  @param res vetor que guarda o resultado. Deve estar previamente alocado e com
 *             seus elementos inicializados em 0.0 (zero)
 *  @return vetor de 'm' elementos
 *
 */

void multMatVet (MatRow mat, Vetor v, int m, int n, Vetor res)
{
  LIKWID_MARKER_REGISTER("1-n");
  LIKWID_MARKER_START("1-n");

  /* Efetua a multiplicação */
  if (res) {
    for (int i=0; i < m; ++i)
      for (int j=0; j < n; ++j)
        res[i] += mat[n*i + j] * v[j];
  }

  LIKWID_MARKER_STOP("1-n");
}

/**
 *  Funcao multMatRowVet:  Efetua multiplicacao entre matriz 'mxn' por vetor
 *                       de 'n' elementos
 *  @param mat matriz 'mxn'
 *  @param m número de linhas da matriz
 *  @param n número de colunas da matriz
 *  @param res vetor que guarda o resultado. Deve estar previamente alocado e com
 *             seus elementos inicializados em 0.0 (zero)
 *  @return vetor de 'm' elementos
 *
 */
void multMatRowVet(restrict MatRow mat, restrict Vetor v, int m, int n, restrict Vetor res){
  LIKWID_MARKER_REGISTER("1-o");
  LIKWID_MARKER_START("1-o");

  /* Efetua a multiplicação */
  if (res) {
    //Unroll & jam -> fazer blocking
    //passo = 4
    for (int i=0; i < m-m%4; i+=4){
      for (int j=0; j < n; ++j){
        res[i]   += mat[n*i + j]     * v[j];
        res[i+1] += mat[n*(i+1) + j] * v[j];
        res[i+2] += mat[n*(i+2) + j] * v[j];
        res[i+3] += mat[n*(i+3) + j] * v[j];
      }
    }

    //residuo do laco
    for (int i=m-m%4; i < m; i++){
      for (int j=0; j < n; ++j){
        res[i]   += mat[n*i + j] * v[j];
      }
    }
  }

  LIKWID_MARKER_STOP("1-o");
}

/**
 *  Funcao multMatMat: Efetua multiplicacao de duas matrizes 'n x n' 
 *  @param A matriz 'n x n'
 *  @param B matriz 'n x n'
 *  @param n ordem da matriz quadrada
 *  @param C   matriz que guarda o resultado. Deve ser previamente gerada com 'geraMatPtr()'
 *             e com seus elementos inicializados em 0.0 (zero)
 *
 */

void multMatMat (MatRow A, MatRow B, int n, MatRow C)
{
  LIKWID_MARKER_REGISTER("2-n");
  LIKWID_MARKER_START("2-n");

  /* Efetua a multiplicação */
  for (int i=0; i < n; ++i){
    for (int j=0; j < n; ++j){
      for (int k=0; k < n; ++k){
	      C[i*n+j] += A[i*n+k] * B[k*n+j];
      }
    }
  }

  LIKWID_MARKER_STOP("2-n");
}


/**
 *  Funcao multMatMatRow: Efetua multiplicacao de duas matrizes 'n x n' 
 *  @param A matriz 'n x n'
 *  @param B matriz 'n x n'
 *  @param n ordem da matriz quadrada
 *  @param C   matriz que guarda o resultado. Deve ser previamente gerada com 'geraMatPtr()'
 *             e com seus elementos inicializados em 0.0 (zero)
 *
 */
void multMatMatRow(MatRow A, MatRow B, int n, MatRow C){
  LIKWID_MARKER_REGISTER("2-o");
  LIKWID_MARKER_START("2-o");

  int istart, iend, jstart, jend, kstart, kend;

  for(int ii = 0; ii<n/4; ++ii){
    istart=ii*4; iend=istart+4;
    for(int jj=0; jj<n/4; ++jj){
      jstart=jj*4; jend=jstart+4;
      for(int kk=0; kk<n/4; ++kk){
        kstart=kk*4; kend=kstart+4;
        for (int i=istart; i<iend; ++i){
          for (int j=jstart; j<jend; j+=4){
            for (int k=kstart; k<kend; ++k){
              //Loop Unroll e Jam
              for (int i=istart; i<iend; ++i){
                for (int j=jstart; j<jend; j+=4){
                  C[i*n+j] = C[i*n+j+1] = C[i*n+j+2] = C[i*n+j+3] = 0.0;
                  for (int k=kstart; k<kend; ++k){
                    C[i*n+j]   += A[i*n+k] * B[k*n+j];
                    C[i*n+j+1] += A[i*n+k] * B[k*n+j+1];
                    C[i*n+j+2] += A[i*n+k] * B[k*n+j+2];
                    C[i*n+j+3] += A[i*n+k] * B[k*n+j+3];
                  }
                }
              }

                //Residuo do laco
                for (int j=jend; j < n; ++j){
                  C[i*n+j] = 0.0;
                  for (int k=0; k < n; ++k){
                    C[i*n+j] += A[i*n+k] * B[k*n+j];
                  }
                }
              }
            }
          }
        }
      }
  }

  //residuo da blocagem
  //adiciona valores de fora
  for(int ii = 0; ii<n-n%4; ++ii){
    for(int jj=0; jj<n-n%4; ++jj){
      //linhas/colunas fora dos blocos
      for(int k = n-n%4; k<n; ++k){
        C[ii*n+jj] += A[ii*n+k] * B[k*n+jj];
      }
    }
  }
  //linhas fora dos blocos
  for(int ii = n-n%4; ii<n; ++ii){
    for(int jj=0; jj<n; ++jj){
      C[ii*n+jj] = 0.0;
      for(int kk=0; kk<n; ++kk){
        C[ii*n+jj] += A[ii*n+kk] * B[kk*n+jj];
      }
    }
  }

  //Loop Unroll e Jam
  // for (int i=0; i < n; ++i){
  //   for (int j=0; j < n-n%4; j+=4){
  //     C[i*n+j] = C[i*n+j+1] = C[i*n+j+2] = C[i*n+j+3] = 0.0;
  //     for (int k=0; k < n; ++k){
	//       C[i*n+j]   += A[i*n+k] * B[k*n+j];
  //       C[i*n+j+1] += A[i*n+k] * B[k*n+j+1];
  //       C[i*n+j+2] += A[i*n+k] * B[k*n+j+2];
  //       C[i*n+j+3] += A[i*n+k] * B[k*n+j+3];
  //     }
  //   }
  // }

  //   //Residuo do laco
  //   for (int j=n-n%4; j < n; ++j){
  //     C[i*n+j] = 0.0;
  //     for (int k=0; k < n; ++k){
  //       C[i*n+j] += A[i*n+k] * B[k*n+j];
  //     }
  //   }
  // }


  LIKWID_MARKER_STOP("2-o");
}

/**
 *  Funcao prnMat:  Imprime o conteudo de uma matriz em stdout
 *  @param mat matriz
 *  @param m número de linhas da matriz
 *  @param n número de colunas da matriz
 *
 */

void prnMat (MatRow mat, int m, int n)
{
  for (int i=0; i < m; ++i) {
    for (int j=0; j < n; ++j)
      printf(DBL_FIELD, mat[n*i + j]);
    printf("\n");
  }
  printf(SEP_RES);
}

/**
 *  Funcao prnVetor:  Imprime o conteudo de vetor em stdout
 *  @param vet vetor com 'n' elementos
 *  @param n número de elementos do vetor
 *
 */

void prnVetor (Vetor vet, int n)
{
  for (int i=0; i < n; ++i)
    printf(DBL_FIELD, vet[i]);
  printf(SEP_RES);
}


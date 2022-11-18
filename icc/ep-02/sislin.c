#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "utils.h"
#include "sislin.h"
#include "Metodos.h"

// Alocaçao de matriz em memória. 
SistLinear_t* alocaSisLin (unsigned int n)
{
  SistLinear_t *SL = (SistLinear_t *) malloc(sizeof(SistLinear_t));
  
  if ( SL ) {
    
    SL->n = n;
    SL->A = (real_t **) malloc(n * sizeof(real_t *));
    SL->b = (real_t *) malloc(n * sizeof(real_t));

    if (!(SL->A) || !(SL->b)) {
      liberaSisLin(SL);
      return NULL;
    }

    // Matriz como vetor de N ponteiros para um único vetor com N*N elementos
    SL->A[0] = (real_t *) malloc(n * n * sizeof(real_t));
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

// Liberacao de memória
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


/*!
  \brief Cria coeficientes e termos independentes do SL
  *
  \param SL Ponteiro para o sistema linear
  \param tipo Tipo de sistema linear a ser criado. Pode ser: 
     comSolucao, eqNula, eqProporcional, eqCombLinear, hilbert 
  \param coef_max Maior valor para coeficientes e termos independentes
*/
void iniSisLin (SistLinear_t *SL, tipoSistLinear_t tipo, real_t coef_max)
{
  unsigned int n = SL->n;
  // para gerar valores no intervalo [0,coef_max]
  real_t invRandMax = ((real_t)coef_max / (real_t)RAND_MAX);

  // inicializa vetor b
  for (unsigned int i=0; i<n; ++i) {
    SL->b[i] = (real_t)rand() * invRandMax;
  }
    
  if (tipo == hilbert) {
    for (unsigned int i=0; i<n; ++i) {
      for (unsigned int j=0; j<n; ++j)  {
	SL->A[i][j] = 1.0 / (real_t)(i+j+1);
      }
    }
  }
  else { // inicializa sistema normal e depois altera
    // inicializa a matriz A
    for (unsigned int i=0; i<n; ++i) {
      for (unsigned int j=0; j<n; ++j)  {
	SL->A[i][j] = (real_t)rand() * invRandMax;
      }
    }
    if (tipo == diagDominante) {
      // aumenta o valor dos termos da diagonal principal
      for (unsigned int i=0; i<n; ++i) {
	real_t soma = 0.0;
	for (unsigned int j=0; j < i; ++j) soma += SL->A[i][j];
	for (unsigned int j=i+1; j < n; ++j) soma += SL->A[i][j];
        SL->A[i][i] += soma;
      }
    }
  }
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

void prnVetor (real_t *v, unsigned int n)
{
  int i;

  printf ("\n");
  for(i=0; i < n; ++i)
      printf ("%10g ", v[i]);
  printf ("\n\n");

}


/* funcoes novas */

/*!
  \brief Essa função calcula o resíduo de um sistema linear dado um vetor solucao 

  \param SL Ponteiro para o sistema linear
  \param r Vetor com o Residuo
  \param x Ponteiro com o Vetor solução do sistema 
*/
void calculaResiduo (SistLinear_t *SL, real_t *x, real_t *r)
{
  for(int i = 0; i < SL->n; i++){
    r[i] = SL->b[i];
    for(int j = 0; j < SL->n; j++){
      r[i] -= SL->A[i][j] * x[j];
      if(isnan(r[i]) || isinf(r[i])){
        fprintf(stderr, "\tERRO: GERAÇÃO DE VALORES INF/NAN - Calculo do Residuo\n");
        return;
      }
    }
  }
}

/*!
  \brief Copia valores de uma matriz para outra

  \param SLOrig Ponteiro para o sistema linear de origem
  \param SLDest Ponteiro para o sistema linear de destino
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

/*!
  \brief Checa por erros nos valores de retorno e imprime na saida erros

  \param retornos Vetor com os retornos das funcoes (EGP, GS e REF, nessa ordem)
*/
void checaErros(int *retornos){
  /* para cada retorno, checa por erros */
  for(int i = 0; i < 3; ++i){
    switch(retornos[i]){
      case INFNAN:
        fprintf(stderr, "\tERRO: GERAÇÃO DE VALORES INF/NAN - Metodo Numerico\n");
        break;
      case ALLOC:
        fprintf(stderr, "\tERRO: ERRO DE ALOCAÇÃO\n");
        break;
      case INDET:
        fprintf(stderr, "\tERRO: SISTEMA LINEAR INDETERMINADO\n");
        break;
      case IMPOSS:
        fprintf(stderr, "\tERRO: SISTEMA LINEAR IMPOSSÍVEL\n");
        break;
    }
  }
}

/*!
  \brief Loop que testa matrizes dos tamanhos 10 a 3000

  \param t Tipo do sistema linear (Diag. Dominante, Genérico ou Hilbert)
*/
void testaMatrizes(tipoSistLinear_t t){
  /*
    Aloca dois sistemas, um para EGP (altera o sistema) e uma copia para GS
    e Refinamento (nao alteram o sistema), além de um vetor de solução e um de
    residuo para cada método. Copia resultado do EGP (x1) para o inicio do 
    refinamento (x3)
    Testa em matrizes de tamanho definido (10 -> 3000)
  */
  int TAM_MATRIZES[QTD_MAT] = {10, 30, 50, 128};

  SistLinear_t *SL1, *SL2;
  real_t *x1, *x2, *x3, *r1, *r2, *r3;
  double tEGP = 0.0, tGS = tEGP, tREF = tEGP;

  switch (t){
    case diagDominante:
      printf("Diagonal Dominante: \n");
      break;
    case generico:
      printf("Generica: \n");
      break;
    case hilbert:
      printf("Hilbert: \n");
      break;
    default:
      fprintf(stderr, "ERRO: TIPO DE MATRIZ NÃO RECONHECIDO");
      return;
  }

  printf("   n   |   t_egp   | normaResiduo_egp |    t_gs    |   it_gs   |");
  printf(" normaResiduo_gs |   t_ref   |   it_ref   | normaResiduo_ref|\n");
  printf("-------------------------------------------------------------");
  printf("--------------------------------------------------------------\n");
  for(int i = 0; i < QTD_MAT; i++){
    int tam = TAM_MATRIZES[i];

    /* Testar ponteiros */
    SL1 = alocaSisLin(tam);
    SL2 = alocaSisLin(tam);
    x1 = malloc(sizeof(real_t)*tam);
    x2 = malloc(sizeof(real_t)*tam);
    x3 = malloc(sizeof(real_t)*tam);
    r1 = malloc(sizeof(real_t)*tam);
    r2 = malloc(sizeof(real_t)*tam);
    r3 = malloc(sizeof(real_t)*tam);

    iniSisLin(SL1, t, COEF_MAX);
    copiaMatriz(SL2, SL1, tam);

    int rEGP = eliminacaoGauss(SL1, x1, &tEGP);
    int itGS = gaussSeidel(SL2, x2, ERRO, &tGS);

    for(int i = 0; i < tam; i++){
      x3[i] = x1[i];
    }
    int itREF = refinamento(SL2, x3, ERRO, &tREF);

    calculaResiduo(SL2, x1, r1);
    calculaResiduo(SL2, x2, r2);
    calculaResiduo(SL2, x3, r3);

    printf("%4d   |%10g |   %12g   | %10g |   %4d    |%15g  |", tam, tEGP, normaL2Residuo(SL2, r1), tGS, itGS, normaL2Residuo(SL2, r2));
    printf("%10g |    %4d    | %15g |\n", tREF, itREF, normaL2Residuo(SL2, r3));
  
    int retornos[3] = {rEGP, itGS, itREF};
    checaErros(retornos);

    liberaSisLin(SL1);
    liberaSisLin(SL2);
    free(r1);
    free(r2);
    free(r3);
    free(x1);
    free(x2);
    free(x3);
  }
  printf("\n\n");
}
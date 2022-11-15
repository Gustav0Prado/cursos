#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "utils.h"
#include "sislin.h"
#include "Metodos.h"


/*!
  \brief Troca duas linhas de uma matriz

  \param SL Ponteiro para o sistema linear
  \param b Ponteiro para o vetor com os termos independetes
  \param i Linha a ser trocada
  \param pivo linha a ser trocada
*/
void trocaLinha(SistLinear_t *SL, int i, int pivo)
{
  /* troca valores das linhas */
  for(int j = 0; j < SL->n; j++){
    real_t aux = SL->A[i][j];
    SL->A[i][j] = SL->A[pivo][j];
    SL->A[pivo][j] = aux;
  }

  /* troca valores do vetor de valores independentes */
  real_t auxB = SL->b[i];
  SL->b[i] = SL->b[pivo];
  SL->b[pivo] = auxB;
}

/*!
  \brief Encontra linha com maior valor para pivoteamento

  \param SL Ponteiro para o sistema linear
  \param linha Linha onde inicia a comparação
*/
int encontraMax(SistLinear_t *SL, int linha)
{
  int maior = linha;
  for(int i = linha+1; i < SL->n; i++){
    /* arrumar comparação */
    if((SL->A[i][0] - SL->A[maior][0]) > ERRO){
      maior = i;
    }
  }

  return maior;
}

/*!
  \brief Retrossubstituição em um sistema triangular

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução
*/
void retrossubs(SistLinear_t *SL, real_t *x)
{
  for(int i = SL->n-1; i >= 0; i--){
    x[i] = SL->b[i];
    for(int j = i+1; j < SL->n; j++){
      x[i] -= SL->A[i][j] * x[j];
    }
    x[i] /= SL->A[i][i];
  }
}

/*!
  \brief Método da Eliminação de Gauss

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução
  \param tTotal tempo total em milisegundos gastos pelo método

  \return código de erro. 0 em caso de sucesso.
*/
int eliminacaoGauss (SistLinear_t *SL, real_t *x, double *tTotal)
{
  /* comeca a contar o tempo */
  double tempo = timestamp();

  /* para cada linha do sistema */
  for(int i = 0; i < SL->n; i++){
    /* pivotamento parcial */
    int pivo = encontraMax(SL, i);
    if(pivo != i){
      trocaLinha(SL, i, pivo);
    }

    /* A partir da proxima linha */
    for(int k = i +1; k < SL->n; k++){
      /* zera termos da coluna */
      real_t m = SL->A[k][i] / SL->A[i][i];
      SL->A[k][i] = 0.0;
      /* faz operacao com os outros elementos da linha */
      for(int j = i+1; j < SL->n; j++){
        SL->A[k][j] -= SL->A[i][j] * m;
      }
      /* faz operação com o termo independente */
      SL->b[k] -= SL->b[i] * m;
    }
  }

  /* faz retrossubstituicao e coloca resultados no vetor x */
  retrossubs(SL, x);

  /* mede tempo ao final */
  *tTotal = timestamp() - tempo;

  /* checar se realmente zerou as colunas? */
  return 0;
}


/*!
  \brief Método de Gauss-Seidel

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução
  \param erro menor erro aproximado para encerrar as iterações
  \param tTotal tempo total em milisegundos gastos pelo método

  \return código de erro. Um nr positivo indica sucesso e o nr
          de iterações realizadas. Um nr. negativo indica um erro.
  */
int gaussSeidel (SistLinear_t *SL, real_t *x, real_t erro, double *tTotal)
{
  /* resultado errado quando matriz eh generica ou hilbert */
  /* testar se converge */
  int it = 0;
  real_t errAcum = 0.0;

  double tempo = timestamp();

  /* chute inicial = 0 */
  for(int i = 0; i < SL->n; i++){
    x[i] = 0;
  }

  do{
    errAcum = x[0];

    /* para cada linha, calcula o novo x baseado no chute */
    for(int i = 0; i < SL->n; i++){
      real_t soma  = 0.0;
      /* realiza a soma baseada nos valores das soluções */
      for(int j = 0; j < SL->n; j++){
        if(i != j){
          soma -= SL->A[i][j]*x[j];
        }
      }
      /* calcula o novo x[i] */
      x[i] = (1/SL->A[i][i])*(SL->b[i]+soma);
    }

    /* calcula diferença absoluta entre atual e anterior */
    errAcum = fabs(x[0] - errAcum);

    it++;
  }while(errAcum > erro && it < MAXIT);

  //calcula tempo gasto
  *tTotal = timestamp() - tempo;

  /* erro se gerar nan ou inf */
  return it;
}

/* algoritmo de kahan */
real_t somaKahanQ( real_t *dados, int tam ){
	real_t soma = 0.0f;
	real_t c = 0.0f;

	for(int i = 0; i < tam; i++){
		real_t y = (dados[i]*dados[i]) - c;
		real_t t = soma + y;
		c = (t - soma) - y;
		soma = t;
	}

	return soma;
}



real_t somaParQ( real_t *dados, int tam )
{
	if (tam == 2)
		return (dados[0]*dados[0]) + (dados[1]*dados[1]);
	if (tam == 1)
		return (dados[0]*dados[0]);

	unsigned int div = tam / 2;

	return somaParQ(dados, div) + somaParQ(dados+div, tam-div);
}


/*!
  \brief Essa função calcula a norma L2 do resíduo de um sistema linear 

  \param SL Ponteiro para o sistema linear
  \param r Vetor com o Residuo
*/
real_t normaL2Residuo(SistLinear_t *SL, real_t *r)
{
  /* achar jeito melhor de calcular pra evitar erro -> Kahan????? */
  real_t somaq = 0.0;
  for(int i = 0; i < SL->n; i++){
    somaq += (r[i] * r[i]);
  }

  return sqrt(somaq);
}


/*

*/
void calculaResiduo (SistLinear_t *SL, real_t *x, real_t *r)
{
  for(int i = 0; i < SL->n; i++){
    for(int j = 0; j < SL->n; j++){
      r[i] += SL->A[i][j] * x[j];
    }
    r[i] =  SL->b[i] - r[i];
  }
}


/*!
  \brief Método de Refinamento

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução
  \param erro menor erro aproximado para encerrar as iterações
  \param tTotal tempo total em milisegundos gastos pelo método

  \return código de erro. Um nr positivo indica sucesso e o nr
          de iterações realizadas. Um nr. negativo indica um erro.
  */
int refinamento (SistLinear_t *SL, real_t *x, real_t erro, double *tTotal)
{
  double tParcial;
  double somatParc = 0.0;
  real_t *r = malloc(sizeof(real_t)*SL->n);
  real_t *w = malloc(sizeof(real_t)*SL->n);
  SistLinear_t *A = alocaSisLin(SL->n);
  double tempo = timestamp();
  int it = 0;

  for(int i = 0; i < SL->n; i++){
    r[i] = 0.0;
  }

  /* r = b-Ax */
  calculaResiduo(SL, x, r);

  /* para quando norma < erro ou it >= MAXIT */
  do{
    /* cria novo sistema linear com r como variaveis independentes */
    for(int i = 0; i < SL->n; i++){
      for(int j = 0; j < SL->n; j++){
        A->A[i][j] = SL->A[i][j];
      }
    }
    
    for(int i = 0; i < SL->n; i++){
      A->b[i] = r[i];
    }

    A->n = SL->n;

    /* chama eliminacaoGauss para resolver o sistma */
    eliminacaoGauss(A, w, &tParcial);

    /* obtem proxima solucao -> x(i+1) = x(i) + w */
    for(int i = 0; i < SL->n; i++){
      x[i] += w[i];
    }

    /* r = b-Ax */
    calculaResiduo(SL, x, r);

    it++;
    somatParc += tParcial;
  } while(normaL2Residuo(SL, r) > erro && it < 15);

  *tTotal = timestamp() - tempo + somatParc; 

  liberaSisLin(A);
  free(w);
  free(r);

  return it;
}
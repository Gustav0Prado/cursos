#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

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

  \return código de erro. 0 em caso de sucesso.
*/
int retrossubs(SistLinear_t *SL, real_t *x)
{
  /*Checa se sistema eh indeterminado*/
  for(int i = SL->n-1; i >= 0; i--){
    x[i] = SL->b[i];
    for(int j = i+1; j < SL->n; j++){
      x[i] -= SL->A[i][j] * x[j];
    }
    if(!x[i] && !SL->b[i])
      return INDET;
    else if(!x[i] && SL->b[i] != 0)
      return IMPOSS;
    x[i] /= SL->A[i][i];
  }

  return 0;
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
      /* checar se eh inf ou nan */
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
  /* checa se retrosubs nao retornou erro */
  int retro = retrossubs(SL, x);

  /* mede tempo ao final */
  *tTotal = timestamp() - tempo;

  /* checar se realmente zerou as colunas? */
  return retro;
}

real_t normaMax(real_t *ant, real_t *novo, int tam)
{
  real_t maior = novo[0] - ant[0];
  for(int i = 1; i < tam; i++){
    if((novo[i] - ant[i]) > maior){
      maior = novo[i] - ant[i];
    }
  }

  return maior;
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
  int ret;
  real_t maxErr;

  double tempo = timestamp();

  /* testar criterio de convergencia????? */

  /* chute inicial = 0 */
  for(int i = 0; i < SL->n; i++){
    x[i] = 0;
  }

  do{
    /* para cada linha, calcula o novo x baseado no chute */
    for(int i = 0; i < SL->n; i++){
      real_t soma  = SL->b[i];
      real_t err = x[i];
      maxErr = -1.0;

      /* realiza a soma baseada nos valores das soluções */
      for(int j = 0; j < SL->n; j++){
        /* soma todos os elementos menos A[i][i] */
        if(i != j){
          soma -= SL->A[i][j]*x[j];
        }
      }

      /* calcula o novo x[i] */
      soma /= SL->A[i][i];
      if( isinf(soma) || isnan(soma) ){
        ret = INFNAN;
      }
      /* checar se soma nao eh inf ou nan */
      x[i] = soma;

      real_t diff = fabs(x[i] - err);
      /* se diferenca atual > maxErr, atualiza maxErr */
      maxErr = (diff > maxErr) ? diff : maxErr;
    }
    it++;
  } while(maxErr > erro && it < MAXIT);

  //calcula tempo gasto
  *tTotal = timestamp() - tempo;

  ret = (ret == INFNAN) ? ret : it;

  return ret;
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
    somaq += pow(r[i], 2);
    if( isnan(r[i]) || isinf(r[i]) || isnan(somaq) || isinf(somaq) ){
      fprintf(stderr, "\tERRO: GERAÇÃO DE VALORES INF/NAN - Calculo da Norma\n");
      return -1;
    }
  }

  return sqrt(somaq);
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
  /* checar mallocs */
  real_t *r = malloc(sizeof(real_t)*SL->n);
  real_t *w = malloc(sizeof(real_t)*SL->n);
  SistLinear_t *A = alocaSisLin(SL->n);
  double tempo = timestamp();
  int it = 0;
  real_t norma;
  int ret = 0;

  for(int i = 0; i < SL->n; i++){
    r[i] = 0.0;
  }

  /* residuo inicial X0 */
  calculaResiduo(SL, x, r);

  /* para quando norma < erro ou it >= MAXIT */
  do{
    /* cria novo sistema linear com r como variaveis independentes */
    /* memcpy?? */
    for(int i = 0; i < SL->n; i++){
      for(int j = 0; j < SL->n; j++){
        A->A[i][j] = SL->A[i][j];
      }
    }
    
    /* copia residuo como b do Sistema Linear */
    /* memcpy?? */
    for(int i = 0; i < SL->n; i++){
      A->b[i] = r[i];
    }

    A->n = SL->n;

    /* chama eliminacaoGauss para resolver o sistma */
    /* checar por erros na eliminacao*/
    eliminacaoGauss(A, w, &tParcial);

    /* cancelamento subtrativo????????? */
    /* obtem proxima solucao -> x(i+1) = x(i) + w */
    for(int i = 0; i < SL->n; i++){
      x[i] += w[i];
    }

    /* r = b-Ax */
    calculaResiduo(SL, x, r);

    it++;
    somatParc += tParcial;
    norma = normaL2Residuo(SL, r);
  } while(norma > erro && it < MAXIT);

  /* se norma for MUITO grande, nao converge */

  *tTotal = timestamp() - tempo + somatParc; 

  /* funcao pra checar ret */
  if(ret != INFNAN){
    ret = it;
  }

  liberaSisLin(A);
  free(w);
  free(r);

  return ret;
}
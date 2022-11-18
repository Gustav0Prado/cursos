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
  /* troca valores das linhas e depois do vetor de valores independentes */
  for(int j = 0; j < SL->n; j++){
    real_t aux = SL->A[i][j];
    SL->A[i][j] = SL->A[pivo][j];
    SL->A[pivo][j] = aux;
  }

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
  /*
    Faz a retrosubstituição em um sistema triangular, checa se sistema
    é indeterminado ou impossivel (0 = 0 ou 0 = n)
  */
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
  /*
    Para cada linha do sistema, realiza pivotamento parcial, zera os
    termos das colunas e realiza as mesmas operações com o resto da
    linha e o termo independente. No final, faz retrossubstituicao
    e coloca resultados no vetor x 
  */
  double tempo = timestamp();

  for(int i = 0; i < SL->n; i++){
    int pivo = encontraMax(SL, i);
    if(pivo != i){
      trocaLinha(SL, i, pivo);
    }

    for(int k = i +1; k < SL->n; k++){
      /* checar se eh inf ou nan */
      real_t m = SL->A[k][i] / SL->A[i][i];
      SL->A[k][i] = 0.0;
      for(int j = i+1; j < SL->n; j++){
        SL->A[k][j] -= SL->A[i][j] * m;
      }
      SL->b[k] -= SL->b[i] * m;
    }
  }

  int retro = retrossubs(SL, x);

  *tTotal = timestamp() - tempo;

  return retro;
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
  /* 
    Para cada linha, calcula o novo x baseado no chute inicial (0) e
    realiza a soma baseada nos valores das soluções, soma
    "isola" A[i][i] e soma os outros elementos multiplicados pelo x[j],
    essa soma se torna o novo x[i] e ao final calcula a diferenca do x[i]
    atual para o anterior, pega a maior dentre todas as linhas e usa para
    comparar com o erro
  */
  int it = 0;
  int ret;
  real_t maxErr;

  double tempo = timestamp();

  /* testar criterio de convergencia????? */

  for(int i = 0; i < SL->n; i++){
    x[i] = 0;
  }

  do{
    for(int i = 0; i < SL->n; i++){
      real_t soma  = SL->b[i];
      real_t err = x[i];
      maxErr = -1.0;

      for(int j = 0; j < SL->n; j++){
        if(i != j){
          soma -= SL->A[i][j]*x[j];
        }
      }

      soma /= SL->A[i][i];
      if( isinf(soma) || isnan(soma) ){
        ret = INFNAN;
      }
      x[i] = soma;

      real_t diff = fabs(x[i] - err);
      maxErr = (diff > maxErr) ? diff : maxErr;
    }
    it++;
  } while(maxErr > erro && it < MAXIT);

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
  /*
    Calcula um residuo inicial baseado em X0 (resultado do EGP), cria um novo
    sistema linear A com r como os termos independentes, resolve Aw = r por EGP
    soma w com x para obter X(i+1) e calcula o novo residuo para esse X(i+1),
    que será usado para calcular a norma
  */
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

  calculaResiduo(SL, x, r);

  do{
    /* memcpy?? */
    for(int i = 0; i < SL->n; i++){
      for(int j = 0; j < SL->n; j++){
        A->A[i][j] = SL->A[i][j];
      }
    }
    
    /* memcpy?? */
    for(int i = 0; i < SL->n; i++){
      A->b[i] = r[i];
    }

    A->n = SL->n;

    /* checar por erros na eliminacao*/
    eliminacaoGauss(A, w, &tParcial);

    /* cancelamento subtrativo????????? */
    for(int i = 0; i < SL->n; i++){
      x[i] += w[i];
    }

    calculaResiduo(SL, x, r);

    it++;
    somatParc += tParcial;
    norma = normaL2Residuo(SL, r);
  } while(norma > erro && it < MAXIT);

  *tTotal = timestamp() - tempo + somatParc; 

  if(ret != INFNAN){
    ret = it;
  }

  liberaSisLin(A);
  free(w);
  free(r);

  return ret;
}
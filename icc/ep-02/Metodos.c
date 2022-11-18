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
  //troca valores das linhas
  for(int j = 0; j < SL->n; j++){
    real_t aux = SL->A[i][j];
    SL->A[i][j] = SL->A[pivo][j];
    SL->A[pivo][j] = aux;
  }

  //troca valores dos termos independentes
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
  //para cada linha, de baixo pra cima 
  for(int i = SL->n-1; i >= 0; i--){
    x[i] = SL->b[i];
    for(int j = i+1; j < SL->n; j++){
      x[i] -= SL->A[i][j] * x[j];
    }

    //checa se algum valor eh inf ou nan
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
  double tempo = timestamp();

  //para cada linha do sistema
  for(int i = 0; i < SL->n; i++){
    //pivoteamento parcial
    int pivo = encontraMax(SL, i);
    if(pivo != i){
      trocaLinha(SL, i, pivo);
    }

    //para cada linha depois
    for(int k = i +1; k < SL->n; k++){
      //zera coluna
      real_t m = SL->A[k][i] / SL->A[i][i];
      SL->A[k][i] = 0.0;

      //aplica operacoes nos outros elementos da linha e no termo independente
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
  int it = 0;
  int ret = 0;
  real_t maxErr = 0.0;

  double tempo = timestamp();

  for(int i = 0; i < SL->n; i++){
    x[i] = 0;
  }

  do{
    //para cada linha do sistema
    for(int i = 0; i < SL->n; i++){
      real_t soma  = SL->b[i];
      real_t err = x[i];
      maxErr = -1.0;

      //soma todos os elementos menos A[i][i]
      for(int j = 0; j < SL->n; j++){
        if(i != j){
          soma -= SL->A[i][j]*x[j];
        }
      }

      //X(i+1) = ( b[i]-(soma) ) / A[i][i]
      soma /= SL->A[i][i];
      if( isinf(soma) || isnan(soma) ){
        ret = INFNAN;
      }
      x[i] = soma;

      //compara X(i+1) com X(i), pega apenas o maior erro (de todas as linhas)
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
  \brief Essa função calcula a norma L2 do resíduo de um sistema linear implementando
  a soma de Kahan

  \param SL Ponteiro para o sistema linear
  \param r Vetor com o Residuo
*/
real_t normaL2Residuo(SistLinear_t *SL, real_t *r)
{
  real_t somaq = 0.0;
  real_t c = 0.0;
  for(int i = 0; i < SL->n; i++){
    real_t y = pow(r[i], 2) - c;
    real_t t = somaq + y;
    if( isnan(t) || isinf(t) ){
      fprintf(stderr, "\tERRO: GERAÇÃO DE VALORES INF/NAN - Calculo da Norma\n");
      return -1;
    }
    c = (t - somaq) - y;
    somaq = t;
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
  double tempo = timestamp();
  real_t norma = 100;
  int it = 0;
  int ret = 0;

  real_t *r = malloc(sizeof(real_t)*SL->n);
  real_t *w = malloc(sizeof(real_t)*SL->n);
  SistLinear_t *A = alocaSisLin(SL->n);

  if(!r || !w || !A){
    free(r);
    free(w);
    free(A);
    return ALLOC;
  }

  for(int i = 0; i < SL->n; i++){
    r[i] = 0.0;
  }

  while(norma > erro && it < MAXIT){
    //cria sistema linear novo com r como termos independentes
    for(int i = 0; i < SL->n; i++){
      for(int j = 0; j < SL->n; j++){
        A->A[i][j] = SL->A[i][j];
      }
    }
    
    for(int i = 0; i < SL->n; i++){
      A->b[i] = r[i];
    }

    A->n = SL->n;

    /* checar por erros na eliminacao*/
    eliminacaoGauss(A, w, &tParcial);

    //calcula X(i+1) somando X(i) com w (resultado do EGP)
    for(int i = 0; i < SL->n; i++){
      x[i] += w[i];
    }

    calculaResiduo(SL, x, r);
    norma = normaL2Residuo(SL, r);

    it++;
    somatParc += tParcial;
  }

  *tTotal = timestamp() - tempo + somatParc; 

  if(ret != INFNAN){
    ret = it;
  }

  liberaSisLin(A);
  free(w);
  free(r);

  return ret;
}
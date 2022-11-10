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
  \brief Substitui vetor resultado no sistema original para checar soluções

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução

  \return 1 caso soluções não confiram ou 0 caso confiram
*/
int checaSolucao(SistLinear_t *SL, real_t *x)
{
  real_t *check = malloc(sizeof(real_t)*SL->n);
  for(int i = 0; i < SL->n; i++){
    check[i] = SL->A[i][0]*x[0] + SL->A[i][1]*x[1] + SL->A[i][2]*x[2];
    /* compara se iguais */
    if(fabs(check[i] - SL->b[i]) >= ERRO){
      return 1;
    }
  }

  free(check);

  return 0;
}

/*!
  \brief Método da Eliminação de Gauss

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução
  \param tTotal tempo total em milisegundos gastos pelo método

  \return código de erro. 0 em caso de sucesso.
*/
int eliminacaoGauss (SistLinear_t *SLOrig, SistLinear_t *SL, real_t *x, double *tTotal)
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

  retrossubs(SL, x);
  /* variavel para retorno separada só para colocar dentro da contagem de tempo */
  int ret = checaSolucao(SLOrig, x);

  /* mede tempo ao final */
  tempo = timestamp() - tempo;
  *tTotal = tempo;

  /* checar se realmente zerou as colunas? */
  /* checar solução? */
  return ret;
}


/*!
  \brief Essa função calcula a norma L2 do resíduo de um sistema linear 

  \param SL Ponteiro para o sistema linear
  \param x Solução do sistema linear
*/
real_t normaL2Residuo(SistLinear_t *SL, real_t *x)
{
  /* ??????????????????? */
  real_t somaq = 0.0;
  for(int i = 0; i < SL->n; i++){
    somaq += (x[i] * x[i]);
  }

  return sqrt(somaq);
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
  /* conta num de iteracoes?? */
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

    /* calcula erro entre atual e anterior */
    errAcum = fabs(x[0] - errAcum);

    it++;
  }while(errAcum > erro);

  //calcula tempo gasto
  *tTotal = timestamp() - tempo;

  return it;
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

}
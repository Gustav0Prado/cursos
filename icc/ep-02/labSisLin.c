// Gustavo do Prado Silva - GRR20203942

/*
  A partir dos resultados obtidos (tempos, número de iterações, tamanho do SL)
  responda:

  1. É possível estimar as condições em que o método EGP é mais vantajoso 
  que o método GS?
    Dados os resultados, em sistemas com diagonal dominante, EGP acaba sendo
    mais preciso (residuo menor), especialmente em sistemas de tamanho <= 30,
    onde acaba sendo inclusive mais rapido. Temos também em sistemas genéricos,
    visto que Gauss-Seidel acaba não conseguindo resolver por erros numéricos.
    Já em matrizes de Hilbert, o tempo para calcular é menor que GS, porém com
    resíduo bem maior.
    OBS: Considerando o chute inicial = 0

  OBS: Tempos de refinamento para matrizes de tamanho 3000 ficou MUITO grande mas não consegui arrumar/diminuir isso, nem os valores
  inf/nan no Gauss-Seidel em matrizes Genericas
*/

#include <stdio.h>
#include <math.h>
#include <string.h>

#include "utils.h"
#include "sislin.h"
#include "Metodos.h"

int main ()
{
  // inicializa gerador de números aleatórios
  srand(202202);
  
  testaMatrizes(diagDominante);
  testaMatrizes(generico);
  testaMatrizes(hilbert);
}
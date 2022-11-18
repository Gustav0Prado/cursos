// Gustavo do Prado Silva - GRR20203942

/*
  EGP mais rapido que GS em sistemas diagDominante menores??? (10x10)
  GS nao da bons resultados em matrizes genericas e tem residuo maior em diag
  GS em hilbert tem residuo menor, porem tempo maior
  REF gera residuo muito alto (overflow??) em hilbert, sempre tem tempo alto
  para residuo nao tao diferente
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
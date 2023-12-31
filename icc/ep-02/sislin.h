#ifndef __SISLIN_H__
#define __SISLIN_H__

#define COEF_MAX 32.0 // Valor máximo usado para gerar valores aleatórios de
		      // coeficientes nos sistemas lineares.


/* Codigos de erro para valores inf/nan, erro de alocação, e caso o metodo nao convirja (erro > 10^10) */
#define INFNAN -1
#define ALLOC  -2
#define INDET  -3
#define IMPOSS -4

#define QTD_MAT 9

// Estrutura para definiçao de um sistema linear qualquer
typedef struct {
  real_t **A; // coeficientes
  real_t *b; // termos independentes
  unsigned int n; // tamanho do SL
} SistLinear_t;

// Tipos de matrizes de coeficientes usados pela função 'inicializaSistLinear()'
typedef enum {
    generico = 0,
    hilbert,
    diagDominante
} tipoSistLinear_t;


// Alocaçao e desalocação de matrizes
SistLinear_t* alocaSisLin (unsigned int n);
void liberaSisLin (SistLinear_t *SL);
void iniSisLin (SistLinear_t *SL, tipoSistLinear_t tipo, real_t coef_max);

// Leitura e impressão de sistemas lineares
SistLinear_t *lerSisLin ();
void prnSisLin (SistLinear_t *SL);
void prnVetor (real_t *vet, unsigned int n);

void calculaResiduo (SistLinear_t *SL, real_t *x, real_t *r);
void testaMatrizes(tipoSistLinear_t t);

#endif // __SISLIN_H__


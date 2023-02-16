//Gustavo do Prado Silva - 20203942 
//Rafael Gonçalves dos Santos - 20211798

#ifndef __SISTEMA_H__
#define __SISTEMA_H__

// /* Estrutura de uma matriz com apenas as diagonais */
// typedef struct {
//    double **A;             // coeficientes
//    double *b;               // termos independetes originais
//    int *diagjStart;     // posicoes de inicio
//    int *diagjEnd;       // posicoes de fim
// } MatDiag_t;

// /* Estrutura de uma matriz simetrica */
// typedef struct {
//    double **A;             // coeficientes
//    double *b;               // termos independetes modificados
//    int *simjStart;      // posicoes de inicio
//    int *simjEnd;        // posicoes de fim
// } MatSim_t;

// // Estrutura para definiçao de um sistema linear qualquer
// typedef struct {
//    MatDiag_t Diag;      // Matriz com diagonais (Matriz original)
//    MatDiag_t Sim;       // Matriz principal simetrizada
//    unsigned int n;      // tamanho do SL
//    unsigned int i;      //numero maximo de iteracoes
// } SistLinear_t;

// Estrutura para definiçao de um sistema linear qualquer
typedef struct {
   double **A; // coeficientes
   double *b; // termos independentes
   unsigned int n; // tamanho do SL
   unsigned int i; //numero maximo de iteracoes
} SistLinear_t;

void liberaSisLin (SistLinear_t *SL);

SistLinear_t* alocaSisLin (unsigned int n);
// SistLinear_t* alocaSisLin (unsigned int n, unsigned int k);

void prnSisLin (SistLinear_t *SL);

#endif
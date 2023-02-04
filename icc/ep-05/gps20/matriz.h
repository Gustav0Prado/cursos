/* Constantes */

#define DBL_FIELD "%12.7lg"
#define SEP_RES "\n\n\n"

#define DEF_SIZE 128
#define BASE 32

#define BK 8
#define UF 8

#define ABS(num)  ((num) < 0.0 ? -(num) : (num))

/* Tipos para matrizes e vetores */

typedef double real_t;

typedef real_t * MatRow;
typedef real_t * Vetor;

/* ----------- FUNÇÕES ---------------- */

MatRow geraMatRow (int m, int n, int zerar);
Vetor geraVetor (int n, int zerar);

void liberaVetor (void *vet);

void multMatVet (MatRow mat, Vetor v, int m, int n, Vetor res);
void multMatMat(MatRow A, MatRow B, int n, MatRow C);

void multMatRowVet (restrict MatRow mat, restrict Vetor v, int m, int n, restrict Vetor res);
void multMatMatRow(restrict MatRow A, restrict MatRow B, int n, restrict MatRow C);

void prnMat (MatRow mat, int m, int n);
void prnVetor (Vetor vet, int n);


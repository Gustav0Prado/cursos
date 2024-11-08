#include "set.h"

int ind(Game g, int i, int j) {
    return (i*g.cols + j);
}

int mat(Game g, int x) {
    return g.matrix[x / g.lines][x % g.cols - 1];
}

/**
 * Função que gera recursivamente os subconjuntos de tamanho r e aplica neles uma função f
 */
void generate_subsets(Game g, int *set, int n, int r, int *temp, int index, int i, FILE* file, void (*f)(Game g, int *subset, int size, FILE* file)){
    if (index == r) {
        f(g, temp, r, file);
        return;
    }

    if (i >= n) return;

    temp[index] = set[i];
    generate_subsets(g, set, n, r, temp, index+1, i+1, file, f);
    generate_subsets(g, set, n, r, temp, index  , i+1, file, f);
}
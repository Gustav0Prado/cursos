#include "set.h"


/**
 * Função que converte de índice i e j (linha e coluna) para um índice único
 */
int ind(Game g, int i, int j) {
    return (i*g.cols + j);
}

/**
 * Função que reverte de um índice único para i e j (linha e coluna)
 */
int mat(Game g, int x) {
    return g.matrix[x / g.lines][x % g.cols - 1];
}

/**
 * Função que gera recursivamente os subconjuntos de tamanho r e aplica neles uma função f
 */
void generate_subsets(Game g, Set s, int index, int i, FILE* file, void (*f)(Game g, Set s, FILE* file)){
    if (index == s.subset_size) {
        f(g, s, file);
        return;
    }

    if (i >= s.size) return;

    s.subset[index] = s.arr[i];
    generate_subsets(g, s, index+1, i+1, file, f);
    generate_subsets(g, s, index  , i+1, file, f);
}

/**
 * Função que retorna se um elemento está em um conjunto
 */
int in(int *set, int n, int elem){
    int present = 0;
    for(int i = 0; i < n; ++i){
        if(set[i] == elem)
            present = 1;
    }
    return present;
}
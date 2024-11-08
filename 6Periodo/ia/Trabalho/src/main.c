#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "sat.h"
#include "game.h"

int main() {
    int n, m;
    Game g;

    scanf("%i", &n);
    scanf("%i", &m);

    g.lines = n + 2;
    g.cols  = m + 2;

    /* Aloca matriz */
    g.matrix = malloc(sizeof(int*)*g.lines);
    for (int i = 0; i < g.lines; ++i) {
        g.matrix[i] = malloc(sizeof(int) * g.cols);
    }

    /* Le toda matriz */
    for (int i = 1; i < g.lines-1; ++i) {
        for (int j = 1; j < g.cols-1; ++j) {
            scanf("%i ", &g.matrix[i][j]);
        }
    }

    /**
     * Faz os memes aqui
     */
    int set[8];
    int temp[7];
    FILE* f = fopen("formula.sat", "w");
    pick_neighbors(g, &set, 1, 1);
    generate_subsets(g, set, 8, 7, temp, 0, 0, f, loneliness);

    /* Imprime matriz */
    for (int i = 0; i < g.lines; ++i) {
        for (int j = 0; j < g.cols; ++j) {
            printf("%d ", g.matrix[i][j]);
        }
        printf("\n");
    }

    /* Libera estruturas usadas */
    for (int i = 0; i < n; ++i) {
        free(g.matrix[i]);
    }
    free(g.matrix);
}
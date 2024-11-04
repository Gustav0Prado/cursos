#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    int **game;

    scanf("%i", &n);
    scanf("%i", &m);

    /* Aloca matriz */
    game = malloc(sizeof(int*)*n);
    for (int i = 0; i < n; ++i) {
        game[i] = malloc(sizeof(int) * m);
    }

    /* Le toda matriz */
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%i ", &game[i][j]);
        }
    }

    /**
     * Faz os memes aqui
     */

    /* Imprime matriz */
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d ", game[i][j]);
        }
        printf("\n");
    }

    /* Libera estruturas usadas */
    for (int i = 0; i < n; ++i) {
        free(game[i]);
    }
    free(game);
}
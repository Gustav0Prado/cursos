#include "sat.h"

void loneliness(Game g, int *subset, int size, FILE* file){
    for (int i = 0; i < size; i++) {
        if (mat(g, subset[i]) == 0){
            printf("-%d ", subset[i]);
        }
        else {
            printf("%d ", subset[i]);
        }
    }
    printf("\n");
}
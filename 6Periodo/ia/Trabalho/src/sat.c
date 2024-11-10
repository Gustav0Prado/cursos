#include "sat.h"

/**
 * Função loneliness: Uma célula com menos de 2 vizinhos vivos (pelo menos 7 vizinhos mortos)
 * em t0 está morta em t1
 */
void loneliness(Game g, Set s, FILE* file){
    for (int i = 0; i < s.subset_size; i++) {
        fprintf(file, "%d ", s.subset[i]);
    }
    fprintf(file, "\n");
}

/**
 * Função stagnation: Uma célula morta com exatamente dois vizinhos vivos em t0 vai 
 * continuar morta em t1
 */
void stagnation(Game g, Set s, FILE* file){
    fprintf(file, "%d ", s.elem); // x

    for (int i = 0; i < s.subset_size; i++) {  //not c
        fprintf(file, "-%d ", s.subset[i]);
    }

    for (int i = 0; i < s.size; i++) { // n - c
        if(!(in(s.subset, s.subset_size, s.arr[i]))) {
            fprintf(file, "%d ", s.arr[i]);
        }
    }
    fprintf(file, "\n");
}

/**
 * Função overcrowding: Uma célula com 4 ou mais vizinhos em t0 está morta em t1
 */
void overcrowding(Game g, Set s, FILE* file){
    for (int i = 0; i < s.subset_size; i++) {
        fprintf(file, "-%d ", s.subset[i]);
    }
    fprintf(file, "\n");
}

/**
 * Função preservation: Uma célula viva com exatamente dois vizinhos vivos em t0 vai 
 * continuar viva em t1
 */
void preservation(Game g, Set s, FILE* file){
    fprintf(file, "-%d ", s.elem); // not x

    for (int i = 0; i < s.subset_size; i++) {  //not c
        fprintf(file, "-%d ", s.subset[i]);
    }

    for (int i = 0; i < s.size; i++) { // n - c
        if(!(in(s.subset, s.subset_size, s.arr[i]))) {
            fprintf(file, "%d ", s.arr[i]);
        }
    }
    fprintf(file, "\n");
}

/**
 * Função life: Uma célula com exatamente 3 vizinhos vivos em t0 vai estar viva em t1
 */
void life(Game g, Set s, FILE* file){
    for (int i = 0; i < s.subset_size; i++) {  //not c
        fprintf(file, "-%d ", s.subset[i]);
    }

    for (int i = 0; i < s.size; i++) { // n - c
        if(!(in(s.subset, s.subset_size, s.arr[i]))) {
            fprintf(file, "%d ", s.arr[i]);
        }
    }
    fprintf(file, "\n");
}
#ifndef SET_H
#define SET_H

#include <stdio.h>
#include "game.h"

typedef struct set
{
    int *arr;
    int size;
    int elem;
    int *subset;
    int subset_size;
} Set;

int ind(Game g, int i, int j);
int mat(Game g, int x);
void generate_subsets(Game g, Set s, int index, int i, FILE* file, void (*f)(Game g, Set s, FILE* file));
int in(int *set, int n, int elem);

#endif
#ifndef SET_H
#define SET_H

#include <stdio.h>
#include "game.h"

int ind(Game g, int i, int j);

int mat(Game g, int x);

void generate_subsets(Game g, int *set, int n, int r, int *temp, int index, int i, FILE* file, void (*f)(Game g, int *subset, int size, FILE* file));

#endif
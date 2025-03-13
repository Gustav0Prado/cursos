#ifndef SAT_H
#define SAT_H

#include <stdio.h>
#include "game.h"
#include "set.h"

void loneliness(Game g, Set s, FILE* file);
void stagnation(Game g, Set s, FILE* file);
void overcrowding(Game g, Set s, FILE* file);
void preservation(Game g, Set s, FILE* file);
void life(Game g, Set s, FILE* file);

#endif
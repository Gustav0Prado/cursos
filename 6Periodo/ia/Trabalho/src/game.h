#ifndef GAME_H
#define GAME_H

typedef struct game
{
    int ** matrix;
    int lines;
    int cols;
} Game;


void pick_neighbors(Game g, int (*arr)[], int i, int j);

#endif
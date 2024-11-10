#ifndef GAME_H
#define GAME_H

#define LONELINESS_S_SIZE 7
#define STAGNATION_S_SIZE 2
#define OVERCROWDING_S_SIZE 4
#define PRESERVATION_S_SIZE 2
#define LIFE_S_SIZE 3

typedef struct game
{
    int ** matrix;
    int lines;
    int cols;
    int **res;
} Game;


void pick_neighbors(Game g, int (*arr)[], int i, int j);
void start_game(Game *g);

#endif
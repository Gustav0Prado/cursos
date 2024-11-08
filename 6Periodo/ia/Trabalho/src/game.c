#include "game.h"
#include "set.h"
#include "sat.h"

void pick_neighbors(Game g, int (*arr)[], int i, int j){
    (*arr)[0] = ind(g, i-1, j-1);
    (*arr)[1] = ind(g, i-1, j);
    (*arr)[2] = ind(g, i-1, j+1);
    (*arr)[3] = ind(g, i, j-1);
    (*arr)[4] = ind(g, i, j+1);
    (*arr)[5] = ind(g, i+1, j-1);
    (*arr)[6] = ind(g, i+1, j);
    (*arr)[7] = ind(g, i+1, j+1);
}
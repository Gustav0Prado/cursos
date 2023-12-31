/* WSCAD - 9th Marathon of Parallel Programming
 * Simple Brute Force Algorithm for the
 * Traveling-Salesman Problem
 * Author: Emilio Francesquini - francesquini@ic.unicamp.br
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "utils.h"

int min_distance;
int nb_towns;

typedef struct
{
    int to_town;
    int dist;
} d_info;

d_info **d_matrix;
int *dist_to_origin;

void tsp(int depth, int current_length, char *path, int last)
{
    int i;
    if (current_length >= min_distance)
        return;
    if (depth == nb_towns)
    {
        current_length += dist_to_origin[last];
        if (current_length < min_distance)
            min_distance = current_length;
    }
    else
    {
        int town, me, dist;
        me = last;
        for (i = 0; i < nb_towns; i++)
        {
            town = d_matrix[me][i].to_town;
            if (path[town] == 0)
            {
                path[town] = 1;
                dist = d_matrix[me][i].dist;
                tsp(depth + 1, current_length + dist, path, town);
                path[town] = 0;
            }
        }
    }
}

void greedy_shortest_first_heuristic(int *x, int *y, double *tpar)
{
    int i, j, k, dist;
    int *tempdist;

    double inst_par = timestamp();

    tempdist = (int *)malloc(sizeof(int) * nb_towns);
    // Could be faster, albeit not as didactic.
    // Anyway, for tractable sizes of the problem it
    // runs almost instantaneously.
    for (i = 0; i < nb_towns; i++)
    {
        for (j = 0; j < nb_towns; j++)
        {
            int dx = x[i] - x[j];
            int dy = y[i] - y[j];
            tempdist[j] = dx * dx + dy * dy;
        }

        for (j = 0; j < nb_towns; j++)
        {
            int tmp = INT_MAX;
            int town = 0;
            for (k = 0; k < nb_towns; k++)
            {
                if (tempdist[k] < tmp)
                {
                    tmp = tempdist[k];
                    town = k;
                }
            }
            tempdist[town] = INT_MAX;
            d_matrix[i][j].to_town = town;
            dist = (int)sqrt(tmp);
            d_matrix[i][j].dist = dist;
            if (i == 0)
                dist_to_origin[town] = dist;
        }
    }

    free(tempdist);

    *tpar += timestamp() - inst_par;
}

void init_tsp(double *tpar)
{
    int i, st;
    int *x, *y;

    min_distance = INT_MAX;

    st = scanf("%u", &nb_towns);
    if (st != 1)
        exit(1);

    d_matrix = (d_info **)malloc(sizeof(d_info *) * nb_towns);
    for (i = 0; i < nb_towns; i++)
        d_matrix[i] = (d_info *)malloc(sizeof(d_info) * nb_towns);
    dist_to_origin = (int *)malloc(sizeof(int) * nb_towns);

    x = (int *)malloc(sizeof(int) * nb_towns);
    y = (int *)malloc(sizeof(int) * nb_towns);

    for (i = 0; i < nb_towns; i++)
    {
        st = scanf("%u %u", x + i, y + i);
        if (st != 2)
            exit(1);
    }

    greedy_shortest_first_heuristic(x, y, tpar);

    free(x);
    free(y);
}

int run_tsp(double *tpar)
{
    int i;
    char *path;

    init_tsp(tpar);

    path = calloc(nb_towns, sizeof(char));
    path[0] = 1;

    double inst_par = timestamp();

    tsp(1, 0, path, 0);

    *tpar += timestamp() - inst_par;

    free(path);
    for (i = 0; i < nb_towns; i++)
        free(d_matrix[i]);
    free(d_matrix);

    return min_distance;
}

int main(int argc, char **argv)
{
    double tpar = 0.0;
    double time = timestamp();

    int num_instances, st;
    st = scanf("%u", &num_instances);
    if (st != 1)
        exit(1);
    while (num_instances-- > 0)
        printf("%d ", run_tsp(&tpar));
    printf("\n");

    free(dist_to_origin);

    time = timestamp() - time;
    printf("Tempo total: %lf\n", time/1000);
    printf("Tempo   par: %lf\n", tpar/1000);
    return 0;
}
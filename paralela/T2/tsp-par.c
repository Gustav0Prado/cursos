/* WSCAD - 9th Marathon of Parallel Programming
 * Simple Brute Force Algorithm for the
 * Traveling-Salesman Problem
 * Author: Emilio Francesquini - francesquini@ic.unicamp.br
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <mpi.h>

int min_distance, reduc_min_dist;
int nb_towns, cut;

typedef struct
{
    int to_town;
    int dist;
} d_info;

d_info **d_matrix;
int *dist_to_origin;

void tsp(int depth, int current_length, char *path, int last, int count)
{
    int i;

    if (current_length >= min_distance)
        return;
    if (depth == nb_towns)
    {
        current_length += dist_to_origin[last];
        if (current_length < min_distance)
            min_distance = current_length;
        
        if (count == cut) {
            MPI_Allreduce(&min_distance, &reduc_min_dist, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
            min_distance = reduc_min_dist;
            count = -1;
        }
        count++;
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
                tsp(depth + 1, current_length + dist, path, town, count);
                path[town] = 0;
            }
        }
    }
}

void greedy_shortest_first_heuristic(int *x, int *y)
{
    int i, j, k, dist;
    int *tempdist;

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
}

void init_tsp(int *x, int *y)
{
    int i, st;

    min_distance = INT_MAX;

    d_matrix = (d_info **)malloc(sizeof(d_info *) * nb_towns);
    for (i = 0; i < nb_towns; i++)
        d_matrix[i] = (d_info *)malloc(sizeof(d_info) * nb_towns);
    dist_to_origin = (int *)malloc(sizeof(int) * nb_towns);

    greedy_shortest_first_heuristic(x, y);
}

void run_tsp(int rank, int n_procs)
{
    int i;
    char *path;

    path = calloc(nb_towns, sizeof(char));
    path[0] = 1;

    int start = rank+1;
    int end = start + (nb_towns/n_procs);

    // Divide escolha da segunda cidade entre os processos
    for(int i = start; i < end; i++){
        path[i] = 1;
        tsp(2, dist_to_origin[i], path, i, 0);
        path[i] = 0;
    }

    MPI_Allreduce(&min_distance, &reduc_min_dist, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);

    free(path);
    for (i = 0; i < nb_towns; i++)
        free(d_matrix[i]);
    free(d_matrix);
}

void read_stdin(int **x, int **y){
    int st;
    
    st = scanf("%u", &nb_towns);
    if (st != 1)
        nb_towns = 0;

    *x = malloc(sizeof(int) * nb_towns);
    *y = malloc(sizeof(int) * nb_towns);

    for(int i = 0; i < nb_towns; ++i){
        st = scanf("%u %u", (*x) + i, (*y) + i);
        if (st != 2)
            nb_towns = 0;
    }
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, n_procs, num_instances, st, buff_size;
    int *x, *y;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n_procs);

    double time = MPI_Wtime();
    double init = MPI_Wtime();

    if(rank == 0) {    
        st = scanf("%u", &num_instances);
        if (st != 1)
            num_instances = 0;
    }
    
    // Manda para todos o num de instancias
    MPI_Bcast(&num_instances, 1, MPI_INT, 0, MPI_COMM_WORLD);

    while (num_instances-- > 0)
        if(rank == 0) read_stdin(&x, &y);

        // Broadcast do num de cidades e alocacao do buffer
        MPI_Bcast(&nb_towns, 1, MPI_INT, 0, MPI_COMM_WORLD);
        cut = 50;
        
        // Caso tenha havido algum problema na leitura, finaliza execucao
        if(nb_towns == 0){
            MPI_Finalize();
            return 1;
        }
        else if (rank > 0) {
            x = malloc(sizeof(int) * nb_towns);
            y = malloc(sizeof(int) * nb_towns);
        }
        
        // Broadcast do x e y lidos para os outros processos
        MPI_Bcast(x, nb_towns, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(y, nb_towns, MPI_INT, 0, MPI_COMM_WORLD);

        init_tsp(x, y);
        run_tsp(rank, n_procs);

        if (rank == 0) printf("%d ", reduc_min_dist);
    if (rank == 0) printf("\n");

    free(dist_to_origin);
    free(x);
    free(y);

    time = MPI_Wtime() - time;
    if(rank == 0) printf("Tempo total: %.15f\n", time);

    MPI_Finalize();
    return 0;
}
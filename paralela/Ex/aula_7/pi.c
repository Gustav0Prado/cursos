#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static long num_steps = 100000;
double step;

int main (int argc, char **argv) {
    int my_rank, n_procs;
    char msg[100];
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n_procs);

    int i; double x, pi, sum = 0.0;
    step = 1.0/(double) num_steps;

    int start = my_rank * num_steps/n_procs;
    int end = (my_rank+1) * num_steps/n_procs;

    // printf("start: %d, end: %d\n", start, end);

    for (int i = start; i < end; i++){
        x = (i + 0.5) * step; // Largura do retângulo
        sum = sum + 4.0 / (1.0 + x*x); // Sum += Área do retângulo
    }
    
    pi = step * sum;

    if(my_rank == 0){
        printf("Proc %d: %.10g \n", 0, pi);
        for (int i = 1; i < n_procs; i++) {
            MPI_Recv(msg, 100, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            printf("Proc %d: %.10g \n", status.MPI_SOURCE, atof(msg));
            pi += atof(msg);
        }

        printf("\nPi total: %.10g \n", pi);
    }
    else{
        sprintf(msg, "%.10g", pi);
        MPI_Send(msg, strlen(msg) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}
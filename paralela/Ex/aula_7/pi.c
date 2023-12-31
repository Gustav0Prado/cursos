#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static long num_steps = 100000;
double step;

int main (int argc, char **argv) {
    int my_rank, n_procs;
    double msg;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n_procs);

    double x, pi, sum = 0.0;
    step = 1.0/(double) num_steps;

    for (int i = my_rank; i < num_steps; i+= n_procs){
        x = (i + 0.5) * step; // Largura do retângulo
        sum = sum + 4.0 / (1.0 + x*x); // Sum += Área do retângulo
    }
    
    pi = step * sum;

    if(my_rank == 0){
        printf("Proc %d: %.10g \n", 0, pi);
        for (int i = 1; i < n_procs; i++) {
            MPI_Recv(&msg, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            printf("Proc %d: %.10g \n", status.MPI_SOURCE, msg);
            pi += msg;
        }

        printf("\nPi total: %.10g \n", pi);
    }
    else{
        MPI_Send(&pi, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}
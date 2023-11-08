all: mpi

CFLAGS = -Wall -O3

mpi: laplace.c
	mpicc -o mpi laplace.c $(CFLAGS)

run: mpi
	mpirun --hostfile hosts.txt -np 2 ./mpi

clean:
	rm -f mpi a.out
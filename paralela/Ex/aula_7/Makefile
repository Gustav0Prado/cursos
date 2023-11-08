all: mpi

CFLAGS = -Wall -O3

mpi: pi.c
	mpicc -o mpi pi.c $(CFLAGS)

run: mpi
	mpirun --hostfile hosts.txt -np 8 ./mpi

clean:
	rm -f mpi a.out
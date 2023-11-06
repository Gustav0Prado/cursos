all: mpi

mpi: pi.c
	mpicc -o mpi pi.c -O3

run: mpi
	mpirun --hostfile hosts.txt -np 8 ./mpi

clean:
	rm -f mpi a.out
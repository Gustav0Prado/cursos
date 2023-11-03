all: mpi

mpi: pi.c
	mpicc -o mpi pi.c -O3

run: mpi
	mpirun --hostfile hosts.txt -np 4 ./mpi

clean:
	rm -rf ./mpi
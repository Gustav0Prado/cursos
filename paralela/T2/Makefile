all: utils.o mpi tsp

CFLAGS = -O3 -lm

utils.o: utils.c utils.h
	gcc -c utils.c

mpi: tsp-par.c
	mpicc -o mpi tsp-par.c utils.o $(CFLAGS)

tsp: tsp.c
	gcc -o tsp tsp.c utils.o $(CFLAGS)

run: all
	mpirun --hostfile hosts.txt -np 8 ./mpi < simple.in

clean:
	rm -rf ./mpi ./tsp *.o
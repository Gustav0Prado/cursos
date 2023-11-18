all: utils.o mpi tsp

CFLAGS = -O3 -lm -g

utils.o: utils.c utils.h
	gcc -c utils.c

mpi: tsp-mw.c
	mpicc -o mpi tsp-mw.c utils.o $(CFLAGS)

tsp: tsp.c
	gcc -o tsp tsp.c utils.o $(CFLAGS)

run: clean all
	mpirun --hostfile hosts.txt -np $(p) ./mpi < simple.in

clean:
	rm -rf ./mpi ./tsp *.o
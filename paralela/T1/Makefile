CC = gcc
CFLAGS = -lm -g -fopenmp -Wall -O3

all: utils.o tsp tsp-par tsp-opt

utils.o: utils.c utils.h
	$(CC) -c utils.c

tsp: tsp.c
	$(CC) -o tsp tsp.c utils.o $(CFLAGS)

tsp-par: tsp-par.c
	$(CC) -o tsp-par tsp-par.c utils.o $(CFLAGS)

tsp-opt: tsp-opt.c
	$(CC) -o tsp-opt tsp-opt.c utils.o $(CFLAGS)

clean:
	@echo "Limpando ..."
	@rm -rf *.o ./tsp ./tsp-par ./tsp-opt __pycache__

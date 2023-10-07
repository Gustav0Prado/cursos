CC = gcc
CFLAGS = -lm -g -fopenmp -Wall -O3

all: utils.o tsp tsp-par

utils.o: utils.c utils.h
	$(CC) -c utils.c

tsp: tsp.c tsp-opt.c
	$(CC) -o tsp tsp-opt.c utils.o $(CFLAGS)

tsp-par: tsp-par.c tsp-par_alt.c
	$(CC) -o tsp-par tsp-par_alt.c utils.o $(CFLAGS)

clean:
	@echo "Limpando ..."
	@rm -rf *.o ./tsp ./tsp-par ./tsp-opt __pycache__

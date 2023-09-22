CC = gcc
CFLAGS = -lm -g -fopenmp -Wall -O3

all: tsp tsp-par

tsp: tsp.c
	$(CC) -o tsp tsp.c $(CFLAGS)

tsp-par: tsp-par.c
	$(CC) -o tsp-par tsp-par.c $(CFLAGS)

clean:
	@echo "Limpando ..."
	@rm -rf ./tsp ./tsp-par
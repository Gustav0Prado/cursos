CC = gcc
CFLAGS = -lm -g -fopenmp -Wall -O3

all: tsp tsp-par

tsp: tsp.c
	$(CC) -c utils.c
	$(CC) -o tsp tsp.c utils.o $(CFLAGS)

tsp-par: tsp-par.c
	$(CC) -c utils.c
	$(CC) -o tsp-par tsp-par.c utils.o $(CFLAGS)

clean:
	@echo "Limpando ..."
	@rm -rf ./tsp ./tsp-par __pycache__

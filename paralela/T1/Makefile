CC = gcc
CFLAGS = -lm -g -fopenmp -Wall -O3
SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	@echo "Limpando ..."
	@rm -rf ./tsp ./tsp-par
CC = gcc
CFLAGS = -g -fopenmp -Wall -O3
SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS)  -o $@ $<

clean:
	@echo "Limpando ..."
	@find . -type f -executable -exec rm '{}' \;
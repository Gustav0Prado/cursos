CC = gcc
CFLAGS = -g -fopenmp -Wall
SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS)  -o $@ $<

clean:
	@echo "Limpando ..."
	@find . -type f -executable -exec rm '{}' \;
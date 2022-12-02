CFLAGS = -Wall -g -lm

objects = main.o edo.o utils.o

all: ep03

ep03: $(objects)
	gcc $(objects) -o ep03 $(CFLAGS)

main.o: main.c
	gcc -c main.c $(CFLAGS)

edo.o: edo.c edo.h
	gcc -c edo.c $(CFLAGS)

utils.o: utils.c utils.h
	gcc -c utils.c $(CFLAGS)

clean:
	rm -rf $(objects) ./*~ ./.vscode

purge: clean
	rm -f ./ep03

remake: purge all

CFLAGS = -Wall -g -lm

objects = main.o edo.o utils.o matriz.o

all: ep03

ep03: $(objects)
	gcc $(objects) -o labEdo $(CFLAGS)

main.o: main.c
	gcc -c main.c $(CFLAGS)

edo.o: edo.c edo.h
	gcc -c edo.c $(CFLAGS)

utils.o: utils.c utils.h
	gcc -c utils.c $(CFLAGS)

matriz.o: matriz.c matriz.h
	gcc -c matriz.c $(CFLAGS)

clean:
	rm -rf $(objects) ./*~ ./.vscode

purge: clean
	rm -f ./labEdo

remake: purge all

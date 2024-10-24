CFLAGS = -Wall -lm
objects = ./1 ./2 ./3 ./4

all: $(objects)

./1: 1.c
	gcc -o 1 1.c $(CFLAGS)

./2: 2.c
	gcc -o 2 2.c $(CFLAGS)

./3: 3.c
	gcc -o 3 3.c $(CFLAGS)
	
./4: 4.c
	gcc -o 4 4.c $(CFLAGS)

clean:
	rm -rf $(objects) ./*~ ./.vscode

purge: clean
	rm -rf ./1 ./2 ./3 ./4
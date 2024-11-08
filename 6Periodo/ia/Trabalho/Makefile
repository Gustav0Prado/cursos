all: main

main: src/main.c set.o sat.o game.o
	gcc -o main src/main.c set.o sat.o game.o

set.o: src/set.c
	gcc -c src/set.c

sat.o: src/sat.c
	gcc -c src/sat.c

game.o: src/game.c
	gcc -c src/game.c

clean:
	rm -rf set.o sat.o main
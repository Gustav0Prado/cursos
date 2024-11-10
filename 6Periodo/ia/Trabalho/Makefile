CFLAGS = -g

all: game_of_life

game_of_life: src/main.c dist/set.o dist/sat.o dist/game.o
	gcc -o dist/main src/main.c dist/set.o dist/sat.o dist/game.o $(CFLAGS)
	ln -fs dist/main game_of_life

dist/set.o: src/set.c
	gcc -c src/set.c -o dist/set.o $(CFLAGS)

dist/sat.o: src/sat.c
	gcc -c src/sat.c -o dist/sat.o $(CFLAGS)

dist/game.o: src/game.c
	gcc -c src/game.c -o dist/game.o $(CFLAGS)

clean:
	rm -rf dist/*.o dist/main game_of_life *.sat
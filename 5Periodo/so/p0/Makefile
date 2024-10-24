all: testafila

CFLAGS = -Wall -g

queue.o: queue.c
	gcc -c queue.c $(CFLAGS)

testafila: queue.o testafila.c
	gcc -o testafila testafila.c queue.o $(CFLAGS)

clean:
	rm -f *.o ./testafila

run: all
	./testafila
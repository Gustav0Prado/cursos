all: mundo

mundo: mundo.c libmundo.o libconjunto.o liblef.o libfila.o
	gcc libconjunto.o liblef.o libmundo.o libfila.o -o mundo mundo.c -lm -Wall -g

libmundo.o : libmundo.c
	gcc -c libmundo.c -lm -Wall

libconjunto.o: libconjunto.c
	gcc -c libconjunto.c -Wall

libfila.o: libfila.c
	gcc -c libfila.c -Wall

liblef.o : liblef.c
	gcc -c liblef.c -Wall

clean : 
	rm *.o mundo
run: all
	./mundo
remake: clean all

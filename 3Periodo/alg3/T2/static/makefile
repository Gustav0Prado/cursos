all: myht

myht: libht.o myht.c
	gcc libht.o -o myht myht.c -g -lm

libht.o : libht.c
	gcc -c libht.c -lm

run: all
	./myht

clean:
	rm ./myht libht.o
teste:
	./myht < teste1.in

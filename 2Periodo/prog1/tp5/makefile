all : testa

testa : testa.o libconjunto.o
	gcc libconjunto.o -o testa testa.c -Wall

libconjunto.o : libconjunto.c
	gcc -c libconjunto.c -Wall

clean : 
	rm testa libconjunto.o testa.o

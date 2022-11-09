all: testa_conjunto testa_lista testa_fila

testa_conjunto: testa_conjunto.o libconjunto.o
	gcc -o testa_conjunto testa_conjunto.o libconjunto.o -Wall
testa_conjunto.o: testa_conjunto.c
	gcc -c testa_conjunto.c -Wall
libconjunto.o: libconjunto.c
	gcc -c libconjunto.c -Wall

testa_lista: testa_lista.o liblista.o
	gcc -o testa_lista testa_lista.o liblista.o -Wall
testa_lista.o: testa_lista.c
	gcc -c testa_lista.c -Wall
liblista.o: liblista.c
	gcc -c liblista.c -Wall

testa_fila: testa_fila.o libfila.o
	gcc -o testa_fila testa_fila.o libfila.o -Wall
testa_fila.o: testa_fila.c
	gcc -c testa_fila.c -Wall
libfila.o: libfila.c
	gcc -c libfila.c -Wall

clean : 
	rm testa_fila testa_lista testa_conjunto *.o
run: all
	./testa_conjunto && ./testa_fila && ./testa_lista
remake: clean all
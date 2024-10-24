# Gustavo do Prado Siva
# GRR20203942

CFLAGS = -std=c99 -Wall -D_DEFAULT_SOURCE

objects = opcoes.o learquivos.o bike.o main.o

#regra default
all : gps

gps: $(objects)
	gcc $(objects) -o gps $(CFLAGS)

main.o: main.c
	gcc -c main.c $(CFLAGS)

bike.o: bike.c bike.h
	gcc -c bike.c $(CFLAGS)

opcoes.o : opcoes.c opcoes.h
	gcc -c opcoes.c $(CFLAGS)

learquivos.o : learquivos.c learquivos.h
	gcc -c learquivos.c $(CFLAGS)

#remove objetos e restos do editor
clean:
	rm -rf $(objects) ./*~ ./.vscode ./*.gp

#remove TUDO menos os arquivos fontes
purge: clean
	rm -f ./gps

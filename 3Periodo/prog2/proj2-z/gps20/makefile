# Gustavo do Prado Siva
# GRR20203942

CFLAGS = -std=c99 -Wall -g -lm $$(pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5 --libs --cflags)

objects = jogo.o menu.o fim.o pausa.o grafico.o main.o lista.o jogoutils.o fila.o

all: ballz

ballz: $(objects)
	gcc $(objects) -o ballz $(CFLAGS)

main.o: main.c
	gcc -c main.c $(CFLAGS)

jogo.o: jogo.c jogo.h
	gcc -c jogo.c $(CFLAGS)

menu.o: menu.c menu.h
	gcc -c menu.c $(CFLAGS)

fim.o: fim.c fim.h
	gcc -c fim.c $(CFLAGS)

pausa.o: pausa.c pausa.h
	gcc -c pausa.c $(CFLAGS)

grafico.o: grafico.c grafico.h
	gcc -c grafico.c $(CFLAGS)

lista.o: lista.c lista.h
	gcc -c lista.c $(CFLAGS)

jogoutils.o: jogoutils.c jogoutils.h
	gcc -c jogoutils.c $(CFLAGS)

fila.o : fila.c fila.h
	gcc -c fila.c $(CFLAGS)

clean:
	rm -rf $(objects) ./*~ ./.vscode

purge: clean
	rm -f ./ballz ./score.dat

remake: purge all

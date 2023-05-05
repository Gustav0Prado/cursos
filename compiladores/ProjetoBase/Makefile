 # -------------------------------------------------------------------
 #            Arquivo: Makefile
 # -------------------------------------------------------------------
 #              Autor: Bruno Müller Junior
 #               Data: 08/2007
 #      Atualizado em: [09/08/2020, 19h:01m]
 #
 # -------------------------------------------------------------------

$DEPURA=1

CFLAGS = -ll -ly -lc -g

compilador: lex.yy.c compilador.tab.c compilador.o compilador.h pilha.o tabsimb.o
	gcc lex.yy.c compilador.tab.c compilador.o pilha.o tabsimb.o -o compilador $(CFLAGS)

lex.yy.c: compilador.l compilador.h
	flex compilador.l

compilador.tab.c: compilador.y compilador.h
	bison compilador.y -d -v

compilador.o : compilador.h compiladorF.c
	gcc -c compiladorF.c -o compilador.o

pilha.o : pilha.c pilha.h
	gcc -c pilha.c -o pilha.o

tabsimb.o : tabsimb.c tabsimb.h
	gcc -c tabsimb.c -o tabsimb.o

clean :
	rm -f compilador.tab.* lex.yy.c compilador.o compilador pilha.o tabsimb.o

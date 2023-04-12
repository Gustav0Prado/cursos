 # -------------------------------------------------------------------
 #            Arquivo: Makefile
 # -------------------------------------------------------------------
 #              Autor: Bruno Müller Junior
 #               Data: 08/2007
 #      Atualizado em: [09/08/2020, 19h:01m]
 #
 # -------------------------------------------------------------------

$DEPURA=1

compilador: lex.yy.c compilador.tab.c compilador.o compilador.h stack.o tabsimb.o
	gcc lex.yy.c compilador.tab.c compilador.o stack.o -o compilador -ll -ly -lc

lex.yy.c: compilador.l compilador.h
	flex compilador.l

compilador.tab.c: compilador.y compilador.h
	bison compilador.y -d -v

compilador.o : compilador.h compiladorF.c
	gcc -c compiladorF.c -o compilador.o

stack.o : stack.c stack.h
	gcc -c stack.c -o stack.o

tabsimb.o : tabsimb.c tabsimb.h
	gcc -c tabsimb.c -o tabsimb.o

clean :
	rm -f compilador.tab.* lex.yy.c compilador.o compilador stack.o tabsimb.o

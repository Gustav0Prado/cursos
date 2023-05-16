posfixo: posfixo.tab.c lex.yy.c posfixo.o compilador.o
	gcc lex.yy.c posfixo.tab.c compilador.o -o posfixo -ll -ly -lc

posfixo.tab.c: posfixo.y 
	bison posfixo.y -d -v

lex.yy.c: posfixo.l 
	flex posfixo.l

compilador.o : compiladorF.h compiladorF.c
	gcc -c compiladorF.c -o compilador.o

clean : 
	rm -f posfixo.tab.* lex.yy.c *.o

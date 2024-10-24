all: ppos

CFLAGS = -Wall -g
OBJECTS = queue.o

debug: CFLAGS+= -DDEBUG
debug: ppos

*.o: *.c *.h
	gcc -c $(CFLAGS) $<

ppos: $(OBJECTS) ppos_core.c
	gcc ppos_core.c $(OBJECTS) $(task) $(CFLAGS)

clean:
	rm -rf a.out *.o saida.txt

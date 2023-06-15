all: ppos

CFLAGS = -Wall -g -lm
OBJECTS = queue.o disk.o

debug: CFLAGS+= -DDEBUG
debug: ppos

*.o: *.c *.h
	gcc -c $(CFLAGS) $<

ppos: $(OBJECTS) ppos_core.c
	gcc ppos_core.c $(OBJECTS) $(task) $(CFLAGS) -lrt

clean:
	rm -rf a.out *.o saida.txt

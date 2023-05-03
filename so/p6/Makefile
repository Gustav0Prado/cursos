all: ppos

CFLAGS = -Wall -g
OBJECTS = queue.o

debug: CFLAGS+= -DDEBUG
debug: ppos

*.o: *.c *.h
	gcc -c $(CFLAGS) $<

ppos: $(OBJECTS) ppos_core.c
	gcc $(CFLAGS) ppos_core.c $(OBJECTS) $(task)

clean:
	rm -rf a.out *.o

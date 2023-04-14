all: ppos

CFLAGS = -Wall

debug: CFLAGS+= -DDEBUG
debug: ppos

ppos: ppos_core.c
	gcc $(CFLAGS) ppos_core.c $(task)

clean:
	rm a.out

# GRR20203942 GUSTAVO DO PRADO SILVA
# é necessário compilar com um arquivo de tarefas junto
# use make task=<arquivo com tarefas>
# use make debug task=<arquivo com tarefas> caso queira printfs (coloridos!) de debug

all: check ppos

CFLAGS = -Wextra -g
OBJECTS = queue.o

debug: CFLAGS+= -DDEBUG
debug: ppos

check:
	@[ "${task}" ] || ( echo "Uso: make task=<arquivo com tarefas>.c\nModo (colorido!) de Debug: make debug task=<arquivo com tarefas>.c"; exit 1 )

*.o: *.c *.h
	gcc -c $(CFLAGS) $<

ppos: $(OBJECTS) ppos_core.c
	gcc $(CFLAGS) ppos_core.c $(OBJECTS) $(task)

clean limpa:
	rm -rf a.out *.o

help info:
	@echo "Uso: make task=<arquivo com tarefas>.c"
	@echo "Modo (colorido!) de Debug: make debug task=<arquivo com tarefas>.c"

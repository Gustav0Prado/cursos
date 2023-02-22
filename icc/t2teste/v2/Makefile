# Gustavo do Prado Silva - 20203942 
# Rafael Gonçalves dos Santos - 20211798

CC = gcc -DLIKWID_PERFMON -I${LIKWID_HOME}/include -O3 -march=native
CFLAGS = -g -lm
objects = main.o utils.o sistema.o metodos.o
LFLAGS = -L${LIKWID_HOME}/lib -llikwid

all: cgSolver

cgSolver: $(objects)
	$(CC) $(objects) -o cgSolver $(CFLAGS)  $(LFLAGS)

main.o: main.c oper.h
	$(CC) -c main.c $(CFLAGS) $(LFLAGS)

utils.o: utils.c
	$(CC) -c utils.c $(CFLAGS) $(LFLAGS)

sistema.o: sistema.c
	$(CC) -c sistema.c $(CFLAGS) $(LFLAGS)

metodos.o: metodos.c oper.h
	$(CC) -c metodos.c $(CFLAGS) $(LFLAGS)

#remove objetos e restos do editor
clean:
	rm -rf $(objects) ./*~ ./.vscode ./cgSolver ./*.txt
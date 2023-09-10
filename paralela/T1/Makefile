FLAGS=-lm -g

CC=gcc

RM=rm -f

EXEC=tsp

all: $(EXEC)

$(EXEC): tsp.c
	$(CC) $(EXEC).c -c -o $(EXEC).o $(FLAGS)
	$(CC) $(EXEC).o -o 	 $(EXEC)   $(FLAGS)

run:
	./$(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC)

all : main

CFLAGS = -Wall -g

LO: CFLAGS += -DDEBUG
LO: all

main: socket.o main.c
	gcc -o main main.c socket.o $(CFLAGS)

socket.o: socket.c
	gcc -c socket.c $(CFLAGS)

clean:
	rm -rf ./*.o ./main

dryrun: clean all
	sudo ./main

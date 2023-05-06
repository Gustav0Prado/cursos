all : main

main: socket.o main.c
	gcc -o main main.c socket.o

socket.o: socket.c
	gcc -c socket.c

clean:
	rm -rf ./*.o ./main

dryrun: clean all
	sudo ./main

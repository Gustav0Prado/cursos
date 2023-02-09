all: teste

teste: teste.c malloc.s
	gcc -c malloc.s -g
	gcc -c teste.c -g
	gcc -no-pie -static -o teste teste.o malloc.o

clean:
	rm -f ./malloc ./teste ./*.o
all: myavl

myavl: myavl.c libavl.o
			gcc libavl.o -o myavl myavl.c -g

libavl.o : libavl.c
			gcc -c libavl.c

run: all
		./myavl
clean:
		rm ./myavl libavl.o
teste: all
		./myavl < teste.in

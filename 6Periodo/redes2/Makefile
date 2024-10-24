CFLAGS = -Wall -O3 -g

all: server-tcp

server-tcp: server-tcp.c
	gcc -o server-tcp server-tcp.c $(CFLAGS)

client-tcp: client-tcp.c
	gcc -o client-tcp client-tcp.c $(CFLAGS)

clean:
	rm -f *.o server-tcp client-tcp
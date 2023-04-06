all: main

CFLAGS = -Wall
OBJECTS = stack.o

debug: CFLAGS += -DDEBUG
debug: all

%.o: %.c %.h
	gcc -c $(CFLAGS) $<

main: $(OBJECTS) main.o
	gcc -o $@ $^

clean:
	rm -rf ./main ./*.o
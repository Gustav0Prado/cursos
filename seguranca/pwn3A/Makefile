PROG = pwn3
SRC = main.c
CFLAGS = -fstack-protector-all -Wl,-z,relro,-z,now -w -Xlinker -rpath=./glibc/ -Xlinker -I./glibc/ld-linux-x86-64.so.2 -g

all: compile 

compile:
	@echo "Compiling $(SRC) -> $(PROG)"
	gcc  $(SRC) -o $(PROG) $(CFLAGS)

clean:
	rm -f $(PROG)


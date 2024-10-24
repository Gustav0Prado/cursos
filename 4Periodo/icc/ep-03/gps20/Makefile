    CC     = gcc

    CFLAGS =  -Wall -lm

      PROG = labEdo
      OBJS = utils.o \
             matriz.o \
			 edo.o

%.o: %.c %.h utils.h
	$(CC) -c $(CFLAGS) $<

$(PROG):  $(OBJS) main.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *~ *.bak

purge: clean
	rm -f *.o core a.out
	rm -f $(PROG)
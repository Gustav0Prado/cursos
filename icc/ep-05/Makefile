       PROG   = matmult

           CC = gcc -g
         OBJS = matriz.o

       CFLAGS = -O3 -mavx2 -march=native -DLIKWID_PERFMON -I${LIKWID_INCLUDE} -Wall
       LFLAGS = -lm -L${LIKWID_LIB} -llikwid

.PHONY: all debug clean limpa purge faxina

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

all: $(PROG)

debug:         CFLAGS += -DDEBUG
debug:         $(PROG)

$(PROG):  $(PROG).o

$(PROG): $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean limpa:
	@echo "Limpando ...."
	@rm -f *~ *.bak *.tmp *.txt ./saida/*.txt

purge faxina:   clean
	@echo "Faxina ...."
	@rm -f  $(PROG) *.o core a.out
	@rm -f *.png marker.out *.log

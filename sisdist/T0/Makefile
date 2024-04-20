all: $T

$T: $T.o smpl.o rand.o
	$(LINK.c) -o $@ -Bstatic $T.o smpl.o rand.o -lm

smpl.o: smpl.c smpl.h
	$(COMPILE.c)  -g smpl.c

$T.o: $T.c smpl.h
	$(COMPILE.c) -g  $T.c

rand.o: rand.c
	$(COMPILE.c) -g rand.c

clean:
	$(RM) *.o relat saida; find . -type f -executable -exec rm '{}' \;
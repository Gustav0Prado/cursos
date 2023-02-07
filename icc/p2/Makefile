%: %.c
	gcc -o $@ $< -g -O3 -lm -fopt-info-vec -fopt-info-vec-missed

clean:
	ls | grep -v .c$ | grep -v Makefile | xargs rm
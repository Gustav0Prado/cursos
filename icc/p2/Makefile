%: %.c
	gcc -o $@ $< -g -lm

clean:
	ls | grep -v .c$ | grep -v Makefile | xargs rm
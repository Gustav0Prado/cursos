%: %.c 
	gcc -o $@ $< -O3 -march=native -Wall -falign-functions=32 -falign-loops=32 -fopt-info-vec -funsafe-math-optimizations

clean:
	ls | grep -v .c$ | grep -v Makefile | xargs rm
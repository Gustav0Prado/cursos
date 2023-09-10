integral: integral-seq.c integral-par.c
	gcc -fopenmp -o integral-par integral-par.c -O3
	gcc -o integral-seq integral-seq.c -O3

clean:
	rm -f ./integral-seq ./integral-par a.out
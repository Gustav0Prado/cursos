integral: integral-seq.c integral-par.c integral-par-crit.c integral-par-pfor.c
	gcc -fopenmp -o integral-par integral-par.c -O3
	gcc -fopenmp -o integral-par-crit integral-par-crit.c -O3
	gcc -fopenmp -o integral-par-crit integral-par-pfor.c -O3
	gcc -fopenmp -o integral-pfull integral-pfull.c -O3
	gcc -o integral-seq integral-seq.c -O3

clean:
	rm -f ./integral-seq ./integral-par ./integral-par-crit ./integral-pfull ./integral-par-pfor a.out
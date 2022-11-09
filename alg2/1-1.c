#include <stdio.h>

int fatorial(int n){
	if(n == 0){
		return 1;
	}
	return n * fatorial(n - 1) ;
}

int main(){
	int n;
	scanf("%i", &n);
	printf("%d", fatorial(n));

	return 0;
}

#include <stdio.h>

int expo(int x, int n){
	if(n == 0){
		return 1;
	}
	return x * expo(x, n-1);
}

void main(){
	int i, n;
	scanf("%d %d", &i, &n);
	printf("%d\n", expo(i, n));
}

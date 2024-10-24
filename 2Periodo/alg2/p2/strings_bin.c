#include <stdio.h>

void imprime_vetor(int v[], int n){
   for(int i = 0; i < n; i++){
      printf("%2d", v[i]);
   }
   printf("\n");
}

void backtrack(int v[], int n, int i, int k){
   if(i == n){
      imprime_vetor(v, n);
      return;
   }
   for(int num = 0; num < k; num++){
      v[i] = num;
      backtrack(v, n, i+1, k);
   }
}

void main(){
   int n = 2;
   int vet[n];
   int k = 4;

   backtrack(vet, n, 0, k);
}
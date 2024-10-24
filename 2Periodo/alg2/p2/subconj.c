#include <stdio.h>

void imprime_vetor(int set[], int v[], int n){
   for(int i = 0; i < n; i++){
      if(v[i]){
         printf("%2d ", set[i]);
      }
   }
   printf("\n");
}

/*retorna 1 caso conjunto esteja valido ainda = soma menor que B*/
int conj_valido(int set[], int v[], int i, int B){
   int soma = 0;

   for(int k = 0; k < i; k++){
      if(v[k]){
         soma+= set[k];
      }
   }
   return(soma < B);
}

void bt(int set[], int v[], int n, int i, int B){
   if(i == n){
      imprime_vetor(set, v, n);
      return;
   }
   for(int a = 0; a < 2; a++){
      v[i] = a;
      /*se conjunto nao for valido, passa para o proximo valor, senao, passa para o proximo indice do vetor*/
      if(conj_valido(set, v, i+1, B)){
         bt(set, v, n, i+1, B);
      }
   }
}

void subconjuntos(int set[], int n, int B){
   int v[n];
   bt(set, v, n, 0, B);
}

int main(){
   int set[] = {4, 2, 3, 1};
   int n = 4;
   /*numero a comparar*/
   int B = 4;

   subconjuntos(set, n, B);
}
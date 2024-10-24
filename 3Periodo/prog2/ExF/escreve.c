#include <stdio.h>
#include <stdlib.h>

int main(){
   FILE *arq;
   int *arr = malloc(sizeof(int)*10);
   int j;

   arq = fopen("numeros.dat", "w");
   if(!arq){
      perror("Erro ao abrir arquivo");
      exit(1);
   }

   for(int i = 0; i < 10; i++){
      j = i*10;
      arr[i] = j;
   }

   fwrite(arr, sizeof(int), 10, arq);

   fclose(arq);

   return 0;
}
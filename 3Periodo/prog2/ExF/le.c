#include <stdio.h>
#include <stdlib.h>

int main(){
   FILE *arq;
   int *arr = malloc(sizeof(int)*10);

   arq = fopen("numeros.dat", "r");
   if(!arq){
      perror("Erro ao abrir arquivo");
      exit(1);
   }

   fread(arr, sizeof(int), 10, arq);

   for(int i = 0; i < 10; i++){
      printf("%d\n", arr[i]);
   }


   fclose(arq);

   return 0;
}
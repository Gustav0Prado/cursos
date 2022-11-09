#include <stdio.h>
#include <stdlib.h>

int tamString(char *str){
   int i = 0;
   while(str[i] != '\0'){
      i++;
   }

   return i;
}

char *subString(char *str, char *sub){
   int tamsub = tamString(sub);
   int j;

   for(int i = 0; i <= (tamString(str)-tamsub+1); i++){
      j = 0;
      while(j < tamsub && str[i+j] == sub[j]){
         j++;
      }
      if(j == tamsub){
         return &str[i+j-tamsub];
      }
   }

   return NULL;
}

char *charString(char *str, char a){
   for(int i = 0; i <= tamString(str); i++){
      if(str[i] == a){
         return &str[i];
      }
   }

   return NULL;
}

char *copiaString(char *dest, char *orig){
   int tam = tamString(orig);

   for(int i = 0; i <= tam; i++){
      dest[i] = orig[i];
   }
   dest[tam] = '\0';

   return dest;
}

char *duplicaString(char *str){
   char *novastr = malloc(tamString(str)+1);
   if(novastr != NULL){
      return copiaString(novastr, str);
   }
   return NULL;
}

int comparaString(char *a, char *b){
   int tamA = tamString(a);
   int tamB = tamString(b);
   int menor;

   if(tamA > tamB){
      menor = tamB;
   }
   else{
      menor = tamA;
   }

   for(int i = 0; i <= menor; i++){
      if(a[i] > b[i]){
         return 1;
      }
      else if(a[i] < b[i]){
         return -1;
      }
   }

   return 0;
}

int main(){
   char *nome = "Joao da Silva";
   char *copia = malloc(sizeof(char)*14);

   printf("%d\n%s\n%s\n\n", tamString(nome), subString(nome, "Silva"), charString(nome, 'd'));
   printf("%s\n%s\n\n", copiaString(copia, nome), duplicaString(nome));
   printf("%d\n", comparaString(nome, "JOao da silva"));

   return 0;
}
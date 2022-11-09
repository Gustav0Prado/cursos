#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * removeChar(char * str, char charToRemmove){
   char *s = malloc(sizeof(str));
   int i, j;
   int len = strlen(str);

   strcpy(s, str);
   for(i=0; i<len; i++)
   {
      if(s[i] == charToRemmove)
      {
         for(j=i; j<len; j++)
         {
            s[j] = s[j+1];
         }
         len--;
         i--;
      }
   }
   return s;
}

char * appendChar(char *str, char c){
   char *s = malloc(sizeof(str));

   strcpy(s, str);
   strcat(s, &c);

   return s;
}

void permutar(char *pronto, char *restante){
   int tam = strlen(restante);

   if(tam == 0){
      printf("%s\n", pronto);
      return;
   }
   else{
      for(int i = 0; i < tam; i++){
         permutar(appendChar(pronto, restante[i]), removeChar(restante, restante[i]));
      }
   }
}

void main(){
   permutar("\0", "ABC\0");
}
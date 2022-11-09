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

/*acha todas as permutacoes de "restante"*/
void permutar(char *pronto, char *restante){
   int tam = strlen(restante);

   if(tam == 0){
      printf("perm: %s\n", pronto);
      if(strcmp(pronto, "fila12") == 0){
         printf("Senha Encontrada!\n");
         exit(0);
      }
      return;
   }
   else{
      for(int i = 0; i < tam; i++){
         permutar(appendChar(pronto, restante[i]), removeChar(restante, restante[i]));
      }
   }
}

/*acha todos os subconjuntos de "restante"*/
void subconj(char *pronto, char *restante){
   char c;
   int tam = strlen(restante);

   if(tam == 0){
      //printf("%s\n", pronto);
      if(strlen(pronto) == 6){
         permutar("\0", pronto);
      }
      return;
   }
   else{
      c = restante[0];
      subconj(appendChar(pronto, c), removeChar(restante, c));
      subconj(pronto, removeChar(restante, c));
   }
}


void main(){
   subconj("", "abcdefil21");
}
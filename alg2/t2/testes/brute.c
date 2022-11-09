#include <stdio.h>
#include <string.h>

#define tam_senha 6
#define qtd_char 36

int bruteforce(char str[], char senha[], int tamstr, int tamsenha, int pos_atual){
   if(pos_atual == tamsenha){
      if(strcmp(senha, "6bf04z") == 0){
         printf("Senha Descoberta! %s\n", senha);
         return 1;
      }
      return 0;
   }
   for(int i = 0; i < tamstr; i++){
      senha[pos_atual] = str[i];
      if(bruteforce(str, senha, tamstr, tamsenha, pos_atual+1)){
         return 1;
      }
   }
   return 0;
}

int main(){
   /*coloca elementos possiveis (letras + numeros) em uma string*/
   char *str = "abcdefghijklmnopqrstuvwxyz0123456789";
   char senha[tam_senha] = "";

   return bruteforce(str, senha, qtd_char, tam_senha, 0);
}
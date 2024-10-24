#include <stdio.h>
#include <string.h>

#define tam_senha 6
#define qtd_char 36

/*retorna 1 se tem repeticao*/
int tem_repeticao(char senha[], int tamatual){
   int i = 0;
   char sentinela = senha[tamatual-1];   

   while(senha[i] != sentinela){
      i++;
   }
   return(i != tamatual-1);
}

/*retorna se a senha e valida ou nao, tendo no minimo 2 letras e 2 numeros e sem repeticao*/
int senhavalida(char senha[], int tamatual, int *letras, int *numeros){
   /*97 a 122 = letras ascii, altera a variavel letras para poder cheacar apenas a posicao mais recente*/
   if(senha[tamatual-1] >= 97){
      (*letras)++;
   }
   /*48 a 57 = numeros ascii = letras ascii*/
   else{
      (*numeros)++;
   }

   /*no minimo duas letras e dois numeros = no maximo 4 letras ou 4 numeros*/
   return(*numeros <=4 && *letras <= 4 && !tem_repeticao(senha, tamatual));
}


/*funcao de backtracking*/
int back(char str[], char senha[], int tamstr, int tamsenha, int pos_atual, int letras, int numeros){
   if(pos_atual == tamsenha){
      if(strcmp(senha, "6bf04z") == 0){
         printf("Senha Descoberta! %s\n", senha);
         return 1;
      }
      return 0;
   }
   for(int i = 0; i < tamstr; i++){
      senha[pos_atual] = str[i];
      if(senhavalida(senha, pos_atual+1, &letras, &numeros)){
         if(back(str, senha, tamstr, tamsenha, pos_atual+1, letras, numeros)){
            return 1;
         }
      }
      /*backtrack*/
      if(senha[pos_atual] >= 97){
         letras--;
      }
      else{
         numeros--;
      }
   }
   return 0;
}

int main(){
   /*coloca elementos possiveis (letras + numeros) em uma string*/
   char *str = "abcdefghijklmnopqrstuvwxyz0123456789";
   char senha[tam_senha] = "";

   //return back(str, senha, qtd_char, tam_senha, 0);
   return back(str, senha, qtd_char, tam_senha, 0, 0, 0);
}
/*
//   usando o backtracking consegui reduzir os logins bastante, mas o tempo bem pouco
//   ou ate um pouco maior, nao se deveria ser assim, mas foi o que consegui fazer
*/

#include "biblioteca.h"
#include "quebrador-senha.h"

#define tam_senha 6
#define qtd_char 36

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*retorna 1 se tem repeticao*/
int tem_repeticao(char senha[], int tamatual){
   int i = 0;
   char sentinela = senha[tamatual-1];   

   while(senha[i] != sentinela){
      i++;
   }
   return(i != tamatual-1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*funcao de backtracking*/
/*funcao de backtracking*/
int backtrack(char str[], char senha[], int tamstr, int tamsenha, int pos_atual, int letras, int numeros){
   if(pos_atual == tamsenha){
      return(login(senha));
   }
   for(int i = 0; i < tamstr; i++){
      senha[pos_atual] = str[i];
      if(senhavalida(senha, pos_atual+1, &letras, &numeros)){
         if(backtrack(str, senha, tamstr, tamsenha, pos_atual+1, letras, numeros)){
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*funcao de forca bruta*/
/*obs: itera de a ate z e pula para o char 0, essa versao eh mais rapida do que uma string com os caracteres (em tempo)*/
int bruteforce(char *str, char senha[], int tamstr, int tamsenha, int pos_atual){
   char i;
   
   if(pos_atual == tamsenha){
      return(login(senha));
   }
   for(int i = 0; i < tamstr; i++){
      senha[pos_atual] = str[i];
      if(bruteforce(str, senha, tamstr, tamsenha, pos_atual+1)){
         return 1;
      }
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Retorna 1 caso tenha encontrado a senha e 0 caso contrario */
int quebrador_senha_exaustivo(){
   /*coloca elementos possiveis (letras + numeros) em uma string*/
   char *str = "abcdefghijklmnopqrstuvwxyz0123456789";
   char senha[tam_senha] = "";

   return bruteforce(str, senha, qtd_char, tam_senha, 0);
}

/* Retorna 1 caso tenha encontrado a senha e 0 caso contrario */
int quebrador_senha_poda(){
   /*coloca elementos possiveis (letras + numeros) em uma string*/
   char *str = "abcdefghijklmnopqrstuvwxyz0123456789";
   char senha[tam_senha] = "";

   return backtrack(str, senha, qtd_char, tam_senha, 0, 0, 0);
}
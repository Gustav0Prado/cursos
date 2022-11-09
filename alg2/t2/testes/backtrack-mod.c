#include <stdio.h>
#include <string.h>

#define tam_senha 6

/*retrona se existe repeticao no vetor ou nao*/
int tem_repetido(char senha[], int tamatual){
   /*caso tenha apenas 1 elemento, nao ha repeticoes*/
   if(tamatual == 1){
      return 0;
   }
   /*para cada elemento, procura outro igual no vetor*/
   for(int i = 0; i < tamatual; i++){
      for(int j = i+1; j < tamatual; j++){
         if(senha[i] == senha[j]){
            return 1;
         }
      }
   }
   return 0;
}


int senhavalida(char senha[], int tamatual, int tammax){
   int nums = 0;
   int letras = 0;
   int falta = tammax - tamatual;

   if(falta > 1){
      if(!tem_repetido(senha, tamatual)){
         return 1;
      }
      return 0;
   }
   else{
      for(int i = 0; i < tamatual; i++){
         if(senha[i] <= 122 && senha[i] >= 97){
            letras++;
         }
         else if(senha[i] <= 57 && senha[i] >= 48){
            nums++;
         }
      }
      if(nums >= 2-falta && letras >= 2-falta && !tem_repetido(senha, tamatual)){
         return 1;
      }
      return 0;
   }
}


/*funcao de backtracking*/
int back(char *str, char senha[], int tamstr, int tamsenha, int pos_atual){
   if(pos_atual == tamsenha){
      if(strcmp(senha, "f6a4s9") == 0){
         printf("Senha Descoberta! %s\n", senha);
         return 1;
      }
      return 0;
   }
   for(int i = 0; i < tamstr; i++){
      senha[pos_atual] = str[i];
      if(senhavalida(senha, pos_atual+1, tamsenha)){
         if(back(str, senha, tamstr, tamsenha, pos_atual+1)){
            return 1;
         }
      }
   }
   return 0;

}

int main(){
   /*coloca elementos possiveis (letras + numeros) em uma string*/
   char *str = "abcdefghijklmnopqrstuvwxyz0123456789";
   char senha[tam_senha] = "";

   back(str, senha, 36, tam_senha, 0);
}
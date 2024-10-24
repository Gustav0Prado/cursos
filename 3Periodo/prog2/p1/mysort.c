#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int imprimeRevRepet(char **linhas, int cont){
   int unico = 1;

   for(int i = cont-1; i > -1; i--){
      unico = 1;
      for(int j = i-1; j >= 0; j--){
         if(strcmp(linhas[i], linhas[j]) == 0){
            unico = 0;
         }
      }
      if(unico){
         printf("%s\n", linhas[i]);
      }
   }

   return 0;
}

int imprimeSemRepet(char **linhas, int cont){
   int unico = 1;

   for(int i = 0; i < cont; i++){
      unico = 1;
      for(int j = i+1; j < cont-1; j++){
         if(strcmp(linhas[i], linhas[j]) == 0){
            unico = 0;
         }
      }
      if(unico){
         printf("%s\n", linhas[i]);
      }
   }

   return 0;
}

int imprime(char **linhas, int tam, int flag){
   switch(flag){
      case 0:
         for(int i = 0; i < tam; i++){
            printf("%s\n", linhas[i]);
         }
         break;
      case 1:
         for(int i = tam-1; i > -1; i--){
            printf("%s\n", linhas[i]);
         }
         break;
      case 2:
         imprimeSemRepet(linhas, tam);
         break;
      case 3:
         imprimeRevRepet(linhas, tam);
         break;
      default:
         fprintf(stderr, "Use as opcoes apenas uma vez\n");
         break;
   }

   return 0;
}

/*funcao de comparacao para o qsort*/
int sortString(const void *a, const void *b){
   const char *Sa = *(char **)a;
   const char *Sb = *(char **)b;
   return(strcmp(Sa, Sb));
}

/*ordena usando qsort*/
int ordena(char **linhas, int tam){
   qsort(linhas, tam, sizeof(char*), sortString);

   return 0;
}

int leArquivo(char ***linhas, FILE *arq, int cont){
   char linha[101];
   /*aloca para cada linha lida*/
   fgets(linha, 101, arq);
   while(!feof(arq)){
      (*linhas) = realloc(*linhas, sizeof(char *)*(cont+1));
      (*linhas)[cont] = malloc(sizeof(char)*101);
      strcpy((*linhas)[cont], linha);
      (*linhas)[cont][strlen(linha)-1] = '\0';
      cont++;
      fgets(linha, 101, arq);
   }

   return cont;
}

int main(int argc, char *argv[]){
   char linha[101];
   char **linhas = NULL;
   FILE *arq;
   int cont = 0;
   int opt;
   int flag = 0;

   if(argc < 2){
      cont = 0;
      while(fgets(linha, 101, stdin)){
         linhas = realloc(linhas, sizeof(char *)*(cont+1));
         linhas[cont] = malloc(sizeof(char)*101);
         strcpy(linhas[cont], linha);
         linhas[cont][strlen(linha)-1] = '\0';
         cont++;
      }
      ordena(linhas, cont);
      for(int i = 0; i < cont; i++){
         printf("%s\n", linhas[i]);
      }
   }
   else{
      while((opt = getopt(argc, argv, "ru")) != -1){
         switch(opt){
            case 'r':
               flag += 1;
               break;
            case 'u':
               flag += 2;
               break;
         }
      }
      for(int i = optind; i < argc; i++){
         /*abre arquivos*/
         arq = fopen(argv[i], "r");
         if(!arq){
            perror("Erro ao abrir arquivo");
            continue;
         }

         cont = leArquivo(&linhas, arq, cont);
         fclose(arq);
      }
      ordena(linhas, cont);
      imprime(linhas, cont, flag);
   }

   for(int i = 0; i < cont; i++){
      free(linhas[i]);
   }
   free(linhas);
}
#include "jogo.h"
#include "menu.h"
#include "fim.h"

int main(){

   /*Jogo segue máquina de estados até fechar*/
   Estado state = INICIO;
   Game jogo = iniciaJogo(W, H);

   while(state != -1){
      switch(state){
         /*passa estado para as funcoes?*/
         case INICIO: state = Inicia(&jogo); break;
         case JOGANDO: state = Jogo(&jogo); break;
         case FINALPART: state = Fimpart(&jogo); break;
         case FINAL: state = Termina(&jogo); break;
         default: break;
      }
   }

   return 0;
}
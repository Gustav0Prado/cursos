#include "libfila.h"
#include <stdio.h>


int main(){
   fila_t *f, *f2;
   int elemento;

   f = cria_fila();
   f2 = cria_fila();
   if(f != NULL){
      insere_fila(f, 1);
      insere_fila(f, 2);
      insere_fila(f, 3);
      insere_fila(f, 4);
      insere_fila(f, 5);

      /*testes das operacoes*/
      if(!retira_fila(f, &elemento) || elemento != 1){
         printf("Erro ao remover do inicio da fila\n");
      }
      inicializa_atual_fila(f);
      incrementa_atual_fila(f);
      if(!retira_atual_fila(f, &elemento) || elemento != 3){
         printf("Erro ao remover atual da fila\n");
      }

      if(tamanho_fila(f) != 3 || fila_vazia(f)){
         printf("Erro no tamanho da fila\n");
         return 1;
      }
      
      incrementa_atual_fila(f);
      /*atual deve apontar para o ultimo elemento*/
      if(f->atual != f->fim){
         printf("Erro ao incrementar atual\n");
      }
      if(!consulta_atual_fila(f, &elemento) || elemento != (f->fim)->chave){
         printf("Erro ao consultar atual\n");
         return 1;
      }

      if(!fila_vazia(f2)){
         printf("Erro! fila nao vazia\n");
      }
      if(retira_fila(f2, &elemento)){
         printf("Erro ao retirar de fila vazia\n");
      }

      f = destroi_fila(f);
      f2 = destroi_fila(f2);

      if(f != NULL || f2 != NULL){
         printf("Erro ao destruir fila\n");
         return 1;
      }

      

      printf("Testes passaram - fila\n");
      return 0;
   }
   return 0;
}

#include "liblista.h"
#include <stdio.h>

/*analisa a ordenacao*/
int testaord(lista_t *l){
   nodo_t *n = l->ini;
   nodo_t *m = n->prox;

   while(m != NULL){
      if(n->elemento > m->elemento){
         return 0;
      }
      n = m;
      m = m->prox;
   }
   return 1;
}

int main(){
   lista_t *l, *l2;
   int elemento;

   l = cria_lista();
   l2 = cria_lista();

   if(l != NULL && l2 != NULL){
      /*coloca elementos em l*/
      insere_fim_lista(l, 2);
      insere_inicio_lista(l, 1);
      insere_fim_lista(l, 3);
      insere_fim_lista(l, 5);
      insere_inicio_lista(l, 0);
      insere_ordenado_lista(l, 4);
      insere_ordenado_lista(l, -1);
      insere_ordenado_lista(l, -2);

      /*teste das operacoes em l*/
      if(!retira_inicio_lista(l, &elemento)){
         printf("Erro ao retirar elemento do inicio da lista\n");
         return 1;
      }
      if(!retira_fim_lista(l, &elemento)){
         printf("Erro ao retirar elemento do fim da lista\n");
         return 1;
      }
      if(!retira_elemento_lista(l, 2)){
         printf("Erro ao retirar elemento da lista\n");
         return 1;
      }
      if(!retira_elemento_lista(l, 3)){
         printf("Erro ao retirar elemento da lista\n");
         return 1;
      }
      if(!pertence_lista(l, 4)){
         printf("Erro! funcao pertence incorreta\n");
         return 1;
      }
      if(!pertence_lista(l, 1)){
         printf("Erro! funcao pertence incorreta\n");
         return 1;
      }
      if(!pertence_lista(l, 0)){
         printf("Erro! funcao pertence incorreta\n");
         return 1;
      }
      if((tamanho_lista(l) != 4) || lista_vazia(l)){
         printf("Erro no tamanho da lista\n");
      }

      /*testes com insercao ordenada*/
      insere_ordenado_lista(l2, 15);
      insere_ordenado_lista(l2, 14);
      insere_ordenado_lista(l2, -1);
      insere_ordenado_lista(l2, -2);
      insere_ordenado_lista(l2, 1);
		insere_ordenado_lista(l2, 14);
      insere_ordenado_lista(l2, 25);

      if(!testaord(l2)){
         printf("Erro na insercao ordenada\n");
         return 1;
      }
      if((tamanho_lista(l2) != 7) || lista_vazia(l2)){
         printf("Erro no tamanho da lista\n");
         return 1;
      }

      l = destroi_lista(l);
      l2 = destroi_lista(l2);

      if(l != NULL || l2 != NULL){
         printf("Erro ao destruir listas\n");
         return 1;
      }

      printf("Testes passaram - lista\n");
      return 0;
   }
   return 1;
}

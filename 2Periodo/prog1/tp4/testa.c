#include "libconjunto.h"
#include <stdlib.h>
#include <stdio.h>

/*checa se o conjunto realmente está ordenado e sem repetição*/
int testaord(conjunto_t *c){
   for(int i = 1; i < (c->card); i++){
      if(c->v[i] > c->v[i+1]){
         return 0;
      }
   }
   return 1;
}

/*tenta inserir elementos repetidos e inserir em vetor até o tamanho maximo*/
int testainsercao(conjunto_t *c){
   for(int i = 0; i <= c->max; i++){   
      if(insere(c->v[i], c) == 1){
         return 0;
      }
   }
   return 1;
}

/*testa a uniao dos conjuntos conhecidos c2 e c3*/
int testauniao(conjunto_t *uni){
   for(int i = 0; i <= 10; i++){
      if(i != uni->v[i+1]){
         printf("%d %d\n", i, uni->v[i]);
         return 0;
      }
   }
   return 1;
}

/*testa interseccao dos conjuntos c2 e c1*/
int testainter(conjunto_t *inter){
   if((inter->v[1] != 0) || (inter->v[2] != 8)){
      return 0;
   }
   return 1;
}

/*testa a corretude do conjunto diferenca*/
int testadifer(conjunto_t *difer){
   int vet[4] = {2, 4, 6, 10};
   for(int i = 0; i <= 3; i++){
      if(vet[i] != difer->v[i + 1]){
         return 0;
      }
   }
   return 1;
}

/*retorna 1 caso pertence retorne 0 para algum elemento que exite no conjunto*/
/*ou retorne 1 para algum elemento que nao existe*/
int testapertence(conjunto_t *c){
   for(int i = 1; i <= c->card; i++){
      if(!pertence(c->v[i], c)){
         return 0;
      }
   }
   if(pertence(236, c) || pertence(855, c) || pertence(999, c)){
      return 0;
   }
   return 1;
}

/*retira todos os elemntos do conjunto e compara com o vetor vazio*/
/*retorna 0 caso esteja correto, e 1 caso contrario*/
int testaretira(conjunto_t *c){
   conjunto_t *conj = c;
   int tam = c->card;

   for(int i = 1; i <= tam; i++){
      retira(conj->v[1], conj);
   }
   if(!eh_vazio(conj) || conj->card != 0){
      return 0;
   }
   return 1;
}

/*---intuito eh pegar conjuntos conhecidos e testar todas as operacoes----*/
int main(){
   conjunto_t *c1, *c2, *c3, *c4, *c5, *inter, *difer, *uni;
   int v1[4] = {0, 3, 8, 11};
   int v2[6] = {0, 2, 4, 6, 8, 10};
   int v3[6] = {1, 3, 5, 7, 9, 11};
   
   /*cria dois conjuntos com números aleatorios de 0 a 10*/
   c1 = cria_conjunto(4);
   c2 = cria_conjunto(6);
   c3 = cria_conjunto(6);
   c4 = cria_conjunto(6);
   c5 = cria_conjunto(0);
   /*testa se conjuntos sao nulos/erro no malloc*/
   if((c1 != 0) || (c2 != 0) || (c3 != 0)){
      for(int i = 0; i < 4; i++){
         insere(v1[i], c1);
      }
      for(int i = 0; i < 6; i++){
         insere(v2[i], c2);
      }
      for(int i = 0; i < 6; i++){
         insere(v3[i], c3);
      }
      for(int i = 0; i < 6; i++){
         insere(v3[i], c4);
      }

      /*testa conjuntos criados*/
      if(!testaord(c1) || !testaord(c2) || !testaord(c3)){
         printf("Erro! conjunto ordenado ou elemento repetido\n");
      }

      /*realiza todas as operacoes*/
      inter = cria_interseccao(c1, c2);
      difer = cria_diferenca(c2, c1);
      uni = cria_uniao(c2, c3);

      /*testes sobre as operacoes com os conj definidos*/
      if(contido(c1, c2) || contido(c2, c3) || !contido(c3, c4) || !contido(difer, c2)){
         printf("Erro! relação de contecao incorreta\n");
         return 1;
      }
      if(cardinalidade(c1) != 4 || cardinalidade(c2) != 6 || cardinalidade(c3) != 6){
         printf("Erro! cardinalidade incorreta\n");
         return 1;
      }
      if(eh_vazio(c1) || eh_vazio(c2) || eh_vazio(c3) || eh_vazio(c3) || !eh_vazio(c5)){
         printf("Erro! conjuntos estão vazios\n");
         return 1;
      }
      if(!testapertence(c1) || !testapertence(c2) || !testapertence(c3)){
         printf("Erro! pertinencia incorreta\n");
         return 1;
      }
      if(sao_iguais(c1, c2) || sao_iguais(c2, c3) || !sao_iguais(c3, c4)){
         printf("Erro! igualdade de conjuntos invalida\n");
         return 1;
      }
      if(!testauniao(uni)){
         printf("Erro! uniao dos conjuntos c2 e c3 está incorreta\n");
         return 1;
      }
      if(!testainter(inter)){
         printf("Erro! interseccao dos conjuntos c1 e c2 está incorreta\n");
         return 1;
      }
      if(!testadifer(difer)){
         printf("Erro! diferenca dos conjuntos c2 e c1 está incorreta\n");
         return 1;
      }
      if(!testaretira(c4)){
         printf("Erro! elementos nao estao sendo retirados\n");
         return 1;
      }
		
		imprime(c1);
		imprime(c2);
      imprime(c3);
		imprime(c4);
      imprime(c5);

      /*destroi todos os conjuntos*/
      destroi_conjunto(c1);
      destroi_conjunto(c2);
      destroi_conjunto(c3);
      destroi_conjunto(c4);
      destroi_conjunto(c5);
      destroi_conjunto(inter);
      destroi_conjunto(difer);
      destroi_conjunto(uni);

      printf("Testes passaram\n");
      return 0;
   }
   else{
      printf("Erro! Alocação do conjunto retornou erro");
      return 1;
   }
}

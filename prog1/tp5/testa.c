#include "libconjunto.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*usa dois conjuntos pequenos, um com pares e outro com imparesa interseccao tem de ser vazia,
a uniao ser todos os numeros 1-12, e a diferenca é o proprio conjunto com os pares
os outros dois sao testes da copia e a copia da copia e tem de ser iguais ao original
*/
int main(){
   conjunto_t *c, *c2, *c3, *c4, *sub, *inter, *uni, *dif;

   c = cria_conjunto(6);
   c2 = cria_conjunto(6);
   if(c != NULL && c2 != NULL){
      //*coloca os elementos no conjunto*//
      insere_conjunto(c, 2);
      insere_conjunto(c, 4);
      insere_conjunto(c, 6);
      insere_conjunto(c, 8);
      insere_conjunto(c, 10);
      insere_conjunto(c, 12);

      insere_conjunto(c2, 1);
      insere_conjunto(c2, 3);
      insere_conjunto(c2, 5);
      insere_conjunto(c2, 7);
      insere_conjunto(c2, 9);
      insere_conjunto(c2, 11);

      /*cria conjuntos com as operacoes*/
      c3 = cria_copia(c);
      c4 = cria_copia(c3);
      uni = cria_uniao(c, c2);
      inter = cria_interseccao(c, c2);
      dif = cria_diferenca(c, c2);

      srand(time(0));
      sub = cria_subconjunto(c, 3);

      /*testa as operacoes*/
      if(cardinalidade(c) != c->card){
         printf("Erro! cardinalidade incorreta\n");
         return 1;
      }
      if(!sao_iguais(c, c3) || !sao_iguais(c, c4)){
         printf("Erro! conjunto copia esta incorreto\n");
         return 1;
      }
      if(!contido(sub, c)){
         printf("Erro! subconjunto incorreto, nao esta contido no original\n");
         return 1;
      }
      if(pertence(c4, retirar_um_elemento(c4))){
         printf("Erro! elemento ainda pertence ao conjunto apos retirar\n");
         return 1;
      }
      if(!sao_iguais(dif, c)){
         printf("Erro! diferenca de conjuntos incorreta\n");
         return 1;
      }
      if(!conjunto_vazio(inter)){
         printf("Erro! interseccao incorreta\n");
         return 1;
      }

      for(int i = 1; i <= 12; i++){
         if(i != uni->v[i]){
            printf("Erro! uniao incorreta\n");
            return 1;
         }
      }
      while(c4->card > 0){
         retirar_um_elemento(c4);
      }
      if(!conjunto_vazio(c4)){
         printf("Erro! conjunto nao esta vazio apos retirar elementos\n");
         return 1;
      }
   
      if(!redimensiona(c) || c->max != 12){
         printf("Erro ao redimensionar\n");
      }

      printf("Testes passaram\n");

      /*elimina todos os conjuntos*/
      destroi_conjunto(c);
      destroi_conjunto(c2);
      destroi_conjunto(c3);
      destroi_conjunto(c4);
      destroi_conjunto(sub);
      destroi_conjunto(inter);
      destroi_conjunto(dif);
      destroi_conjunto(uni);
   }
}
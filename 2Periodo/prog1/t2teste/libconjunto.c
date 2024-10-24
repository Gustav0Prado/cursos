#include "libconjunto.h"
#include <stdlib.h>
#include <stdio.h>

/*função de busca binária utilizada em algumas funções para procurar elementos no conjunto*/
/*retorna 0 se não achar*/
int BuscaBin(conjunto_t *c, int x, int ini, int fim){
   int m;

   if(ini > fim){
      return 0;
   }
   m = (ini+fim)/2;
   if(x == c->v[m]){
      return m;
   }
   else if(x < c->v[m]){
      return BuscaBin(c, x, ini, m-1);
   }
   return BuscaBin(c, x, m+1, fim);
}

/*
 * Cria um conjunto vazio e o retorna, se falhar retorna NULL.
 * max eh o tamanho maximo do conjunto, isto eh, o tamanho maximo do vetor
*/
conjunto_t * cria_conjunto (int max){
   conjunto_t *conj = malloc(sizeof(conjunto_t));
   int *vet = malloc((max+1) * sizeof(int));

   if(conj != NULL && vet != NULL){
      conj->max = max;
      conj->card = 0;
      conj->v = vet;
      return conj;
   }
   return NULL;
}

// /*
//  * Remove todos os elementos do conjunto, libera espaco e faz com que ele aponte para NULL.
// */
conjunto_t * destroi_conjunto (conjunto_t *c){
   while(!conjunto_vazio(c)){
      retira_conjunto(c, c->v[1]);
   }
   free(c->v);
   c->v=NULL;
   free(c);
   return NULL;
}

/*
 * Retorna 1 se o conjunto esta vazio e 0 caso contrario.
*/
int conjunto_vazio (conjunto_t *c){
   return (c->card == 0);
}

/*
 * Retorna a cardinalidade do conjunto, isto eh, o numero de elementos presentes nele.
*/
int cardinalidade (conjunto_t *c){
   return c->card;
}

/*
 * Insere o elemento no conjunto, garante que nao existam repeticoes.
 * Retorna 1 se a operacao foi bem sucedida, 0 se tenta inserir elemento existente,
 * e retorna -1 em caso de falha por falta de espaco.
*/
int insere_conjunto (conjunto_t *c, int elemento){
   int i;

	if(c->card == c->max){
		return -1;
	}
	else if(pertence(c, elemento) && c->card > 0){
		return 0;
	}
	else{
      c->v[0] = elemento;
      i = c->card;
      while(elemento < c->v[i]){
         c->v[i+1] = c->v[i];
         i--;
      }
      c->v[i+1] = elemento;
      c->card++;

      return 1;
	}
}

/*
 * Remove o elemento elemento do conjunto caso ele exista e o retorna.
 * Retorna 1 se a operacao foi bem sucedida e 0 se o elemento nao existe.
*/
int retira_conjunto (conjunto_t *c, int elemento){
   int indice = BuscaBin(c, elemento, 1, c->card);

   if(indice != 0){
      for(int i = indice; i < c->card; i++){
         c->v[i] = c->v[i+1];
      }
      c->card--;
      return elemento;
   }
   return 0;
}

/*
 * Retorna 1 se o elemento pertence ao conjunto e 0 caso contrario.
*/
int pertence (conjunto_t *c, int elemento){
   return (BuscaBin(c, elemento, 1, c->card) != 0);
}

/*
 * Retorna 1 se o conjunto c1 esta contido no conjunto c2 e 0 caso contrario.
*/
int contido (conjunto_t *c1, conjunto_t *c2){
   int i, j, ok;

   if(c1->card > c2->card){
      return 0;
   }
   else{
      ok = i = j = 1;
      while((i <= c1->card) && (j <= c2->card) && ok){
         if(c1->v[i] < c2->v[j]){
            ok = 0;
         }
         else if(c1->v[i] > c2->v[j]){
            j++;
         }
         else{
            i++;
            j++;
         }
      }
      if(ok && (i > c1->card)){
         return 1;
      }
      return 0;
   }
}

/*
 * Retorna 1 se o conjunto c1 eh igual ao conjunto c2 e 0 caso contrario.
*/
int sao_iguais (conjunto_t *c1, conjunto_t *c2){
   int i;

   if(c1->card != c2->card){
      return 0;;
   }
   else{
      i = 1;
      while((i <= c1->card) && (c1->v[i] == c2->v[i])){
         i++;
      }
      if(i <= c1->card){
         return 0;
      }
      return 1;
   }
}

/*
 * Retorna o endereco do conjunto diferenca entre c1 e c2, nesta ordem.
 * Retorna NULL se a operacao falhou.
*/
conjunto_t * cria_diferenca (conjunto_t *c1, conjunto_t *c2){
   conjunto_t *dif;
   int i, j, k;
   
   i = 1;
   j = 1;
   k = 0;
   dif = cria_conjunto(c1->card);
   if(dif != NULL){
         while(i <= c1->card && j <= c2->card){
         if(c1->v[i] < c2->v[j]){
            k++;
            dif->v[k] = c1->v[i];
            i++;
         }
         else if(c1->v[i] > c2->v[j]){
            j++;
         }
         else{
            i++;
            j++;
         }
      }
      /*copia elementos restantes de c1*/
      for(j = i; j <= c1->card; j++){
         k++;
         dif->v[k] = c1->v[j];
      }
      dif->card = k;
      return dif;
   }
   return NULL;
}

/*
 * Retorna o endereco do conjunto interseccao entre os conjuntos c1 e c2.
 * Retorna NULL se a operacao falhou.
*/
conjunto_t * cria_interseccao (conjunto_t *c1, conjunto_t *c2){
   int i, j, k, menorcard;
   conjunto_t *intersec;

   i = 1;
   j = 1;
   k = 0;
   if(c1->card < c2->card){
      menorcard = c1->card;
   }
   else{
      menorcard = c2->card;
   }
   intersec = cria_conjunto(menorcard);
   if(intersec != NULL){
      while((i <= c1->card) && (j <= c2->card)){
         if(c1->v[i] < c2->v[j]){
            i++;
         }
         else{
            if(c1->v[i] > c2->v[j]){
               j++;
            }
            else{
               k++;
               intersec->v[k] = c1->v[i];
               i++;
               j++;
            }
         }
      }
      intersec->card = k;
      return intersec;
   }
   return NULL;
}

/*
 * Retorna o endereco do conjunto uniao entre os conjuntos c1 e c2.
 * Retorna NULL se a operacao falhou.
*/
conjunto_t * cria_uniao (conjunto_t *c1, conjunto_t *c2){
   conjunto_t *uniao;
   int i, j, k;

   i = 1;
   j = 1;
   k = 0;
   uniao = cria_conjunto(c1->card + c2->card);
   if(uniao != NULL){
      while(i <= c1->card && j <= c2->card){
         k++;
         if(c1->v[i] < c2->v[j]){
            uniao->v[k] = c1->v[i];
            i++;
         }
         else if(c1->v[i] > c2->v[j]){
            uniao->v[k] = c2->v[j];
            j++;
         }
         else{
            uniao->v[k] = c1->v[i];
            i++;
            j++;
         }
      }
      for(int l = i; l <= c1->card; l++){
         k++;
         uniao->v[k] = c1->v[l];
      }
      for(int l = j; l <= c2->card; l++){
         k++;
         uniao->v[k] = c2->v[l];
      }
      uniao->card = k;

      return uniao;
   }
   return NULL;
}

/*
 * Retorna uma copia do conjunto c e 0 caso nao seja possivel.
*/
conjunto_t * cria_copia (conjunto_t *c){
   conjunto_t *c2;

   c2 = cria_conjunto(c->max);
   if(c2 != NULL){
      c2->card = c->card;
      for(int i = 1; i<= c->card; i++){
         c2->v[i] = c->v[i];
      }
      return c2;
   }
   return 0;
}

/*
 * Cria um subconjunto de cardinalidade n com elementos aleatorios do conjunto c.
 * Retorna o conjunto em caso de sucesso e NULL caso contrario.
 * Se o conjunto for vazio, retorna um subconjunto vazio.
 * Se o n >= cardinalidade (c) entao retorna o proprio conjunto c.
 * Supoe que a funcao srand() tenha sido chamada antes.
*/
conjunto_t * cria_subconjunto (conjunto_t *c, int n){
   conjunto_t *sub;

   /*conjunto vazio*/
   if(c->card == 0){
      sub = cria_conjunto(n);
      return sub;
   }
   /*subconjunto maior ou igual ao original*/
   //obs: se retornar c e n uma copia, programa vai vazar e/ou deletar o conjunto original
   else if(n >= c->card){
      sub = cria_copia(c);
      return sub;
   }
   else{
      /*pega n indices aleatorio do vetor, diminui n se conseguir inserir/nao for repetido*/
      sub = cria_copia(c);
      if(sub != NULL){
         while(sub->card > n){
            retirar_um_elemento(sub);
         }
         return sub;
      }
      return NULL;
   }
}

/*
 * Imprime os elementos do conjunto sempre em ordem crescente,
 * mesmo que a estrutura interna nao garanta isso.
*/
void imprime (conjunto_t *c){
   int elemento = 0;

   if(c->card > 0){
      iniciar_iterador(c);
      while (incrementar_iterador(c, &elemento)){
         printf(" %d ", elemento);
      }
      printf("\n");
   }
   else{
      printf(" vazio\n");
   }
}

/*
 * Retorna 1 se conseguiu dobrar o tamanho max do conjunto e 0 caso contrario.
*/
int redimensiona (conjunto_t *c){
   c->v = realloc(c->v, (c->max+1)*sizeof(int)*2);
   if(c->v != NULL){
      c->max = c->max * 2;
      return 1;
   }
   return 0;
}

/*
 * As funcoes abaixo permitem acessar elementos apontados pelo ponteiro 'ptr'.
 * Este ponteiro pode ser inicializado e incrementado, viabilizando
 * a implementacao de um mecanismo iterador.
*/

/*
 * Inicializa o contador que sera usado na funcao incrementar_iterador 
*/
void iniciar_iterador (conjunto_t *c){
   c->ptr = 1;
}

/*
 * Incrementa iterador e retorna o elemento apontado. Retorna 0 se acabou conjunto 
*/
int incrementar_iterador (conjunto_t *c, int *elemento){
   if(c->ptr <= c->card){
      *elemento = c->v[c->ptr];
      c->ptr++;
      return 1;
   }
   return 0;
}

/*
 * Escolhe um elemento qualquer do conjunto para ser removido e o remove.
 * Nao faz teste se conjunto eh vazio, deixa para main fazer isso       
*/
int retirar_um_elemento (conjunto_t *c){
   /*escolhe num aleatorio de c, elementos comecam em 1*/
   int i = rand() % c->card + 1;
   return (retira_conjunto(c, c->v[i]));
}
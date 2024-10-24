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

/*
 * Remove todos os elementos do conjunto, libera espaco e faz com que ele aponte para NULL.
*/
void destroi_conjunto (conjunto_t *c){
   free(c->v);
   free(c);
}

/* retorna 1 se conseguiu dobrar o tamanho max do conjunto e 0 caso contrario */
int redimensiona (conjunto_t *c){
   c->v = realloc(c->v, ((c->max * 2)+1) * sizeof(int));
   if(c != NULL){
      c->max = c->max * 2;
      return 1;
   }
   return 0;
}

/* retorna 1 se o conjunto c1 esta contido no conjunto c2 e 0 caso contrario */
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
 * Retorna a cardinalidade do conjunto, isto eh, o numero de elementos presentes nele.
*/
int cardinalidade (conjunto_t *c){
   return c->card;
}

/*
 * Retorna 1 se o conjunto esta vazio e 0 caso contrario.
*/
int conjunto_vazio (conjunto_t *c){
   return (c->card == 0);
}

/* retorna 1 se o elemento n pertence ao conjunto c e 0 caso contrario   */
int pertence (conjunto_t *c, int n){
   return (BuscaBin(c, n, 1, c->card) != 0);
}

/* retorna 1 se o conjunto c1 eh igual ao conjunto c2 e 0 caso contrario */
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

/* retorna o endereco do conjunto diferenca entre c1 e c2, nesta ordem  */
/* retorna 0 se a operacao falhou                                       */
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
   return 0;
}

/* retorna o endereco do conjunto interseccao entre os conjuntos c1 e c2  */
/* retorna 0 se a operacao falhou                                         */
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
   return 0;
}

/* retorna o endereco do conjunto uniao entre os conjuntos c1 e c2  */
/* retorna NULL se a operacao falhou                                */
conjunto_t * cria_uniao (conjunto_t *c1, conjunto_t *c2){
   conjunto_t *uniao;
   int i, j, k;

   i = 1;
   j = 1;
   k = 0;
   uniao = cria_conjunto(c1->card + c2->card);
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

/* insere o elemento n no conjunto c caso ele nao exista                     */
/* retorna 1 se a operacao foi bem sucedida e retorna 0 se tente inserir     */
/* elemento ja existente (conjuntos nao tem repeticao) e -1 se nao ha espaco */
int insere(conjunto_t *c, int n){
   int i;

	if(c->card == c->max){
		return -1;
	}
	else if(pertence(c, n) && c->card > 0){
		return 0;
	}
	else{
      c->v[0] = n;
      i = c->card;
      while(n < c->v[i]){
         c->v[i+1] = c->v[i];
         i--;
      }
      c->v[i+1] = n;
      c->card++;

      return 1;
	}
}

/* retira o elemento n do conjunto c caso ele exista */
/* retorna 1 se a operacao foi bem sucedida e retorna 0 se nao existe  */
int retira (conjunto_t *c, int n){
   int indice = BuscaBin(c, n, 1, c->card);

   if(indice != 0){
      for(int i = indice; i < c->card; i++){
         c->v[i] = c->v[i+1];
      }
      c->card--;
      return 1;
   }
   return 0;
}

/* retorna uma copia do conjunto c e 0 caso nao seja possivel       */
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

/* cria um subconjunto com elementos aleatorios do conjunto c     */
/* se o conjunto for vazio, retorna um subconjunto vazio          */
/* se o n >= cardinalidade (c) entao retorna o proprio conjunto c */
conjunto_t * cria_subconjunto (conjunto_t *c, int n);

/* imprime os elementos do conjunto sempre em ordem crescente */
/* mesmo que a estrutura interna nao garanta isso             */
void imprime (conjunto_t *c){
   int elemento = 0;

   iniciar_iterador(c);
   while (incrementar_iterador(c, &elemento)){
      printf(" %d ", elemento);
   }
   printf("\n");
}

/* Inicializa o contador que sera usado na funcao incrementar_iterador */
void iniciar_iterador (conjunto_t *c){
   c->ptr = 1;
}

/* Incrementa iterador e retorna o elemento apontado. Retorna 0 se acabou conjunto */
int incrementar_iterador (conjunto_t *c, int *elemento){
   if(c->ptr <= c->card){
      *elemento = c->v[c->ptr];
      c->ptr++;
      return 1;
   }
   return 0;
}

/* Escolhe um elemento qualquer do conjunto para ser removido e o remove. */
/* Nao faz teste se conjunto eh vazio, deixa para main fazer isso         */
int retirar_um_elemento (conjunto_t *c);
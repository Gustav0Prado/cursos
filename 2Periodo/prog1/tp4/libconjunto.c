#include "libconjunto.h"
#include <stdlib.h>
#include <stdio.h>

/*implentação de conjuntos ordeando*/

/*função de busca binária utilizada em algumas funções para procurar elementos no conjunto*/
/*retorna 0 se não achar*/
int BuscaBin(int x, conjunto_t *c, int ini, int fim){
   int m;

   if(ini > fim){
      return 0;
   }
   m = (ini+fim)/2;
   if(x == c->v[m]){
      return m;
   }
   else if(x < c->v[m]){
      return BuscaBin(x, c, ini, m-1);
   }
   return BuscaBin(x, c, m+1, fim);
}


/*tenta alocar espaço para max inteiros, caso consiga retorna um conjunto vazio*/
/*inicia com card = 0 e um vet com tamanho max*/
conjunto_t * cria_conjunto(int max){
   conjunto_t *conj = malloc((2 * sizeof(int)) + sizeof(int*));
   int *vet = malloc((max + 1) * sizeof(int));

   if(conj != NULL){
      conj->max = max;
      conj->card = 0;
      conj->v = vet;
      return conj;
   }
   return 0;
}

/*esvazia o espaço ocupado pelo conjunto*/
void destroi_conjunto(conjunto_t *c){
   free(c->v);
   free(c);
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

/* retorna a cardinalidade do conjunto c */
int cardinalidade (conjunto_t *c){
   return c->card;
}

/* retorna 1 se o conjunto c eh vazio e 0 caso contrario   */
int eh_vazio (conjunto_t *c){
   return (c->card == 0);
}

/* retorna 1 se o elemento n pertence ao conjunto c e 0 caso contrario   */
int pertence (int n, conjunto_t *c){
   return (BuscaBin(n, c, 1, c->card) != 0);
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
/* retorna 0 se a operacao falhou                                   */
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
/*obs: pos inicial eh 1 para facilitar*/
int insere (int n, conjunto_t *c){
	int i;

	if(c->card == c->max){
		return -1;
	}
	else if(pertence(n, c) && c->card > 0){
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
int retira (int n, conjunto_t *c){
   int indice = BuscaBin(n, c, 1, c->card);

   if(indice != 0){
      for(int i = indice; i < c->card; i++){
         c->v[i] = c->v[i+1];
      }
      c->card--;
      return 1;
   }
   return 0;
}

/* imprime os elementos do conjunto sempre em ordem crescente */
/* mesmo que a estrutura interna nao garanta isso             */
void imprime (conjunto_t *c){
   if(c->card > 0){
      for(int i = 1; i <= c->card; i++){
         printf(" %d ", c->v[i]);
      }
   }
   else{
      printf("vazio");
   }
   printf("\n");
}

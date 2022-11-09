#include "libht.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


int h1(int k){
   return k % m;
}

int h2(int k){
   return floor(m*(k * 0.9 - floor(k * 0.9)));
}

int busca(tTabHash T, int k){
   int j = h1(k);
   //slot nulo, não achou
   if(T.T1[j] == NULL){
      return -1;
   }
   //slot marcado como removido ou chave no slot diferente da procurada, procura na tabela 2
   else if(T.T1[j]->removido || T.T1[j]->chave != k){
      return h2(k);
   }
   //chave no slot == chave procurada
   else if(T.T1[j]->chave == k){
      return j;
   }
}

int inserir(tTabHash* T, int k){
   int i;
   int j = h1(k);
   if(T->T1[j] == NULL){
      //cria novo slot
      T->T1[j] = malloc(sizeof(tSlot));
      T->T1[j]->chave = k;
      T->T1[j]->removido = FALSE;
      T->T1[j]->posicao = j;
      T->T1[j]->tabela = 1;
      return j;
   }
   else if(!T->T1[j]->removido){
      i = h2(T->T1[j]->chave);
      //rejeita a chave caso já exista outra naquela posição
      if(T->T2[i] == NULL){
         T->T2[i] = malloc(sizeof(tSlot));
         //copia antigo para a tabela 2
         T->T2[i]->chave = T->T1[j]->chave;
         T->T2[i]->removido = FALSE;
         T->T2[i]->posicao = i;
         T->T2[i]->tabela = 2;
         //insere atual na tabela 1
         T->T1[j]->chave = k;
         T->T1[j]->removido = FALSE;
         T->T1[j]->posicao = j;
         T->T1[j]->tabela = 1;
         return j;
      }
   }
   else if(T->T1[j]->removido){
      //apenas sobrescreve slot
      T->T1[j]->chave = k;
      T->T1[j]->removido = FALSE;
      T->T1[j]->posicao = j;
      T->T1[j]->tabela = 1;
      return j;
   }
   return -1;
}

int remover(tTabHash* T, int k){
   int j = h1(k);
   int i = h2(k);
   //chave esta na tabela 2
   if(T->T2[i] != NULL){
      if(T->T2[i]->chave == k){
         free(T->T2[i]);
         T->T2[i] = NULL;
         return 0;
      }
   }
   //chave na tabela 1, marca como removido
   else if(T->T1[j] != NULL){
      if(T->T1[j]->chave == k){
         T->T1[j]->removido = TRUE;
         return 0;
      }
   }
   return 1;
}

void insereOrd(tSlot* v[], tSlot* x, int tam){
   //insere slots ordenados pelas chaves
   int i = tam-1;
   while(i >= 0 && v[i]->chave > x->chave){
      v[i+1] = v[i];
      i--;
   }
   v[i+1] = x;
}

void imprimeT(tTabHash T){
   tSlot* v[2*m] = {0};
   int tam = 0;
   int i;

   //insere slots da tabela 2
   for(i = 0; i < m; i++){
      if(T.T2[i] != NULL){
         insereOrd(v, T.T2[i], tam);
         tam++;
      }
   }
   //insere slots da tabela 1
   for(i = 0; i < m; i++){
      if(T.T1[i] != NULL){
         if(!T.T1[i]->removido){
            insereOrd(v, T.T1[i], tam);
            tam++;
         }
      }
   }

   //imprime vetor ordenado
   for(i = 0; i < tam; i++){
      printf("%d,T%d,%d\n", v[i]->chave, v[i]->tabela, v[i]->posicao);
   }
}

//da free em todos os ponteiros e estruturas
void destroiTabela(tTabHash T){
   for(int i = 0; i < m; i++){
      if(T.T1[i] != NULL){
         free(T.T1[i]);
      }
      else if(T.T2[i] != NULL){
         free(T.T2[i]);
      }
   }
}
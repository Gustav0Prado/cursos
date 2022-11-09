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

int inserir(tTabHash* T, int k){
   int i;
   int j = h1(k);
   printf("k:%d  j:%d\n", k, j);
   switch (T->T1[j].removido){
      case VAZIO:
         T->T1[j].chave = k;
         T->T1[j].removido = FALSE;
         return j;
      case FALSE:
         //ignora repetidos
         if(T->T1[j].chave != k){
            //aplica segunda hash na chave antiga
            i = h2(T->T1[j].chave);
            T->T2[i].chave = T->T1[j].chave;
            T->T2[i].removido = FALSE;
            T->T1[j].chave = k;
            T->T1[j].removido = FALSE;
            return j;
         }
      case REMOVIDO:
         T->T1[j].chave = k;
         T->T1[j].removido = FALSE;
         return j;
   }
   //não conseguiu inserir (repetição)
   return -1;
}

int busca(tTabHash *T, int k){
   int j = h1(k);
   if(T->T1[j].removido == VAZIO){
      return -1;
   }
   else if(T->T1[j].chave == k){
      return j;
   }
   else{
      return h2(k);
   }
}

int remover(tTabHash *T, int k){
   int i = h2(k);
   int j = h1(k);
   
   if(T->T2[i].chave == k){
      T->T2[i].removido = VAZIO;
   }
   else{
      T->T1[j].removido = REMOVIDO;
   }
   
}

void imprimeT(tTabHash T){
   for(int i = 0; i < m; i++){
      if(T.T2[i].removido == FALSE){
         printf("%d,T2,%d\n", T.T2[i].chave, i);
      }
   }
   for(int i = 0; i < m; i++){
      if(T.T1[i].removido == FALSE){
         printf("%d,T1,%d\n", T.T1[i].chave, i);
      }
   }
}
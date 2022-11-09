#include "libavl.h"
#include <stdlib.h>
#include <stdio.h>

//cria um no com o valor chave
tNo* criaNo(int chave){
   tNo *n = malloc(sizeof(tNo));
   n->dir = NULL;
   n->esq = NULL;
   n->pai = NULL;
   n->chave = chave;
   n->nivel = 0;
   n->balanc = 0;
   return n;
} 

//busca binaria na arvore
tNo* busca(tNo* no, int chave){
   if(no == NULL){
      return NULL;
   }
   if(chave == no->chave){
      return no;
   }
   if(chave < no->chave){
      return busca(no->esq, chave);
   }
   return busca(no->dir, chave);
}

//retorna altura da arvore
int altura(tNo *no){
   int he, hd;
   if (no == NULL){
      return -1;
   };
   he = altura (no->esq);
   hd = altura (no->dir);
   if (he > hd){
      return he+1;
   }
   else{
      return hd+1;
   }
}

//retorna o fator de balanceamento da arvore, pode ser negativo ou positivo
int calcBalanc(tNo *no){
   if(no == NULL){
      return 0;
   }
   return ((altura(no->esq) - altura(no->dir)));
}

//usa pos-ordem para diminuir nivel de uma subarvore
void diminuiNivel(tNo *no){
   if(no == NULL){
      return;
   }
   diminuiNivel(no->esq);
   diminuiNivel(no->dir);
   no->nivel--;
}

//usa pos-ordem para aumentar nivel de uma subarvore
void aumentaNivel(tNo *no){
   if(no == NULL){
      return;
   }
   diminuiNivel(no->esq);
   diminuiNivel(no->dir);
   no->nivel++;
}

//rotacao a esquerda
tNo* rotEsq(tNo *x){
   //rotacao em si
   tNo *y = x->dir;
   x->dir = y->esq;
   if(y->esq != NULL){
      y->esq->pai = x;
   }
   y->pai = x->pai;
   if(x->pai != NULL){
      if(x == x->pai->esq){
         x->pai->esq = y;
      }
      else{
         x->pai->dir = y;
      }
   }
   y->esq = x;
   x->pai = y;
   //ajusta balanceamento dos nodos
   x->balanc = calcBalanc(x);
   y->balanc = calcBalanc(y);
   //ajusta nivel dos nodos
   x->nivel++;
   y->nivel--;
   diminuiNivel(y->dir);
   aumentaNivel(x->esq);
   return y;
}

tNo* rotDir(tNo *x){
   //rotacao em si
   tNo *y = x->esq;
   x->esq = y->dir;
   if(y->dir != NULL){
      y->dir->pai = x;
   }
   y->pai = x->pai;
   if(x->pai != NULL){
      if(x == x->pai->dir){
         x->pai->dir = y;
      }
      else{
         x->pai->esq = y;
      }
   }
   y->dir = x;
   x->pai = y;
   //ajusta balanceamento dos nodos
   x->balanc = calcBalanc(x);
   y->balanc = calcBalanc(y);
   //ajusta nivel dos nodos
   x->nivel++;
   y->nivel--;
   diminuiNivel(y->esq);
   aumentaNivel(x->dir);
   return y;
}

tNo *balanceamento(tNo *no, int chave){
   no->balanc = calcBalanc(no);
   if(no->balanc > 1){
      //zigzig para a esquerda
      if(chave < no->esq->chave){
         no = rotDir(no);
      }
      //zigzag para direita
      else{
         no->esq = rotEsq(no->esq);
         no = rotDir(no);
      }
   }
   else if(no->balanc < -1){
      //zigzig para a direita
      if(chave > no->dir->chave){
         no = rotEsq(no);
      }
      //zigzag para a esquerda
      else{
         no->dir = rotDir(no->dir);
         no = rotEsq(no);
      }
   }
   return no;
}

//inclusao de valor na arvore
tNo *inclui(tNo* no, int chave){
   if(no == NULL){
      return criaNo(chave);
   }
   //chave menor -> inclui no lado esquerdo
   if(chave < no->chave){
      no->esq = inclui(no->esq, chave);
      no->esq->pai = no;
      no->esq->nivel = no->nivel+1;
   }
   //chave maior -> inclui do lado direito
   else{
      no->dir = inclui(no->dir, chave);
      no->dir->pai = no;
      no->dir->nivel = no->nivel+1;
   }
   no = balanceamento(no, chave);
   return no;
}

void transplant(tNo *u, tNo *v){
   if(u->pai != NULL){
      if(u == u->pai->esq){
         u->pai->esq = v;
      }
      else{
         u->pai->dir = v;
      }
   }
   //ajusta pai e nivel do no transplantado
   if(v!=NULL){
      v->pai = u->pai;
      v->nivel = u->nivel;
   }
}

//algoritimo tree-minimum usado como antecessor(mais a esquerda na direita)
tNo* antecessor(tNo* no){
   if(no->dir == NULL){
      return no;
   }
   return antecessor(no->dir);
}

//algoritmo tree-delete usando antecessor, retorna o no que foi transplantado
tNo* treedelete(tNo *raiz, tNo *z){
   tNo *y;
   tNo *raizNova = raiz;
   //casos 1 e 2 -- um ou nenhum filho
   if(z->esq == NULL){
      transplant(z, z->dir);
   }
   else if(z->dir == NULL){
      transplant(z, z->esq);
   }
   //caso 3 -- dois filhos
   else{
      y = antecessor(z->esq);
      transplant(y, y->dir);
      y->esq = z->esq;
      y->dir = z->dir;
      y->esq->pai = y;
      y->dir->pai = y;
      transplant(z, y);
      if(z == raiz){
         raizNova = y;
      }
   }
   return raizNova;
}

//exclusao usando o algoritmo tree-delete, del eh o no a ser deletado
tNo *exclui(tNo *raiz, int chave){
   tNo *del = busca(raiz, chave);
   tNo *cima = del->pai;
   tNo *raizNova = treedelete(raiz, del);
   free(del);
   del = NULL;
   //"sobe" a arovere balanceando
   while(cima != NULL){
      cima->balanc = calcBalanc(cima);
      //lado esquerdo > direito
      if(cima->balanc > 1){
         if(calcBalanc(cima->esq) >= 0){
            raizNova = rotDir(cima);
         }
         else{
            cima->esq = rotEsq(cima->esq);
            raizNova = rotDir(cima);
         }
      }
      //lado direito > esquerdo
      else if(cima->balanc < -1){
         if(calcBalanc(cima->dir) <= 0){
            raizNova = rotEsq(cima);
         }
         else{
            cima->dir = rotDir(cima->dir);
            raizNova = rotEsq(cima);
         }
      }
      //"sobe" na árvore
      cima = cima->pai;
   }
   return raizNova;
}

//impressao em ordem + nivel
void emOrdem(tNo *no){
   if(no == NULL){
      return;
   }
   emOrdem(no->esq);
   printf("%d,%d\n", no->chave, no->nivel);
   emOrdem(no->dir);
}

//destroi a arvore utilizando o pos-ordem(esq, dir, raiz), pois passa pelas folhas antes da raiz
void destroiArvore(tNo *no){
   if(no == NULL){
      return;
   }
   destroiArvore(no->esq);
   destroiArvore(no->dir);
   free(no);
   no = NULL;
}
#include "no.h"
#include <stdio.h>
#include <stdlib.h>
#define COUNT 10

//cria um no com o valor chave
tNo* criaNo(int chave){
   tNo *n = malloc(sizeof(tNo));
   n->dir = NULL;
   n->esq = NULL;
   n->pai = NULL;
   n->chave = chave;
}

//cria e aloca espaco para uma arvore com um no raiz
tArvore* criaArvore(int chave){
   tArvore *t = malloc(sizeof(tArvore));
   tNo *raiz = criaNo(chave);
   t->raiz = raiz;
   return t;
}

//inclusao de valor na arvore
tNo *inclui(tNo* no, int c){
   if(no == NULL){
      return criaNo(c);
   }
   if(c < no->chave){
      no->esq = inclui(no->esq, c);
      no->esq->pai = no;
   }
   else{
      no->dir = inclui(no->dir, c);
      no->dir->pai = no;
   }
   return no;
}

//busca binaria na arvore
tNo* busca(tNo* nodo, int chave){
   if(nodo == NULL){
      return NULL;
   }
   if(chave == nodo->chave){
      return nodo;
   }
   if(chave < nodo->chave){
      return busca(nodo->esq, chave);
   }
   return busca(nodo->dir, chave);
}

//chave de menor valor da arvore
tNo* minimo(tNo* no){
   if(no->esq == NULL){
      return no;
   }
   return minimo(no->esq);
}

//rotacao a esquerda
tNo *rotEsq(tNo *p){
   tNo *q = p->dir;
   p->dir = q->esq;
   q->pai = p->pai;
   p->pai = q;
   if (q->esq != NULL)
      q->esq->pai = p;
   q->pai->esq = q;
   q->esq = p;
   return q;
}

tNo* rotDir(tNo* p){
   tNo *q = p->esq;
   p->esq = q->dir;
   q->pai = p->pai;
   p->pai = q;
   if (q->dir != NULL)
      q->dir->pai = p;
   q->pai->dir = q;
   q->dir = p;
   return q;
}

//impressao em ordem
void emOrdem(tNo *no){
   if(no == NULL){
      return;
   }
   emOrdem(no->esq);
   printf("%i ", no->chave);
   emOrdem(no->dir);
}

//impressao em ordem
tNo* BuscaEmOrd(tNo *no, int chave){
   tNo *esq, *dir;
   if(no == NULL){
      return NULL;
   }
   esq = BuscaEmOrd(no->esq, chave);
   printf("%i ", no->chave);
   if(no->chave == chave){
      return no;
   }
   dir = BuscaEmOrd(no->dir, chave);
   if(esq != NULL){
      return esq;
   }
   else if(dir != NULL){
      return dir;
   }
}

int somaPares(tNo *no){
   int esq = 0;
   int dir = 0;
   if(no == NULL){
      return 0;
   }
   esq+= somaPares(no->esq);
   dir+= somaPares(no->dir);
   if(no->chave%2 != 0){
      return esq+dir+no->chave;
   }
   return esq+dir;
}

tNo* sucessorIt(tNo* no){
   tNo* x = no->dir;
   while(x->esq != NULL){
      x = x->esq;
   }
   return x;
}

void Troca(tNo* no){
   int aux;
   if(no == NULL){
      return;
   }
   Troca(no->esq);
   Troca(no->dir);
   if(no->esq != NULL && no->esq->chave > no->chave){
      aux = no->chave;
      no->chave = no->esq->chave;
      no->esq->chave = aux;
   }
   else if(no->dir != NULL && no->dir->chave > no->chave){
      aux = no->chave;
      no->chave = no->dir->chave;
      no->dir->chave = aux;
   }
}

tNo* BuscaIt(tNo* no, int chave){
   while(no != NULL && no->chave != chave){
      if(chave < no->chave){
         no=no->esq;
      }
      else{
         no=no->dir;
      }
   }
   return no;
}

int altura(tNo *no){
   int he, hd;
   if(no == NULL){
      return -1;
   }
   he = altura(no->esq);
   hd = altura(no->dir);
   if(he > hd){
      return he+1;
   }
   else{
      return hd+1;
   }
}

int ehavl(tNo* no){
   int subesq, subdir;
   if(no == NULL){
      return 1;
   }
   subesq = ehavl(no->esq);
   if(abs(altura(no->esq)-altura(no->dir)) > 1){
      return 0;
   }
   subdir = ehavl(no->dir);
   return (subesq && subdir);
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

//funcao de imprimir a arvore
void print2DUtil(tNo *root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->dir, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->chave);
 
    // Process left child
    print2DUtil(root->esq, space);
}
 
// Wrapper over print2DUtil()
void print2D(tNo *root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);
}

int main(){
   //criacao e inclusoes na arvore
   tArvore *T = criaArvore(4);
   inclui(T->raiz, 6);
   inclui(T->raiz, 7);
   inclui(T->raiz, 5);
   inclui(T->raiz, 2);
   inclui(T->raiz, 3);
   inclui(T->raiz, 1);

   //imprime arvore
   print2D(T->raiz);
   printf("-------------------------------------\n");

   printf("eh avl? %d\n", ehavl(T->raiz));

   //destroi/deleta arvore e libera os ponteiros 
   destroiArvore(T->raiz);
   free(T);
   T = NULL;

   return 0;
}
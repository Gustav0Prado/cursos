#include "no.h"
#include <iostream>

using namespace std;

tNo *inicia(char valor){
   tNo *n = (tNo *)malloc(sizeof(tNo));
   n->valor = valor;
   n->esq = NULL;
   n->dir = NULL;

   return n;
}

tNo* montaarvore(const char *str, int *i){
   tNo *no = NULL;
   if (str[*i] == '(') {
      (*i)++;
      cout << "cria nó: " << str[*i] << "\n";
      no = inicia (str[*i]);
      (*i)++;
      no -> esq = montaarvore(str, i);
      no -> dir = montaarvore(str, i);
      (*i)++;
   }
   return no;
}

void emordem(tNo * no){
   if (no !=NULL){
      emordem(no->esq);
      cout << no->valor;
      emordem(no->dir);
   }
}

void preordem(tNo * no){
   if (no !=NULL){
      cout << no->valor;
      emordem(no->esq);
      emordem(no->dir);
   }
}

void posordem(tNo * no){
   if (no !=NULL){
      emordem(no->esq);
      emordem(no->dir);
      cout << no->valor;
   }
}

int altura (tNo *p) {
   int he, hd;
   if (p == NULL) return -1;
   he = altura (p->esq);
   hd = altura (p->dir);
   if (he > hd)
   return he+1;
   else
   return hd+1;
}

int main(){
   int i = 0;
   tNo *raiz = montaarvore("(F(B(A)(D(C)(E))))", &i);
   cout << "Pré-ordem: ";
   preordem(raiz);
   cout << "\n";
   cout << "Em ordem: ";
   emordem(raiz);
   cout << "\n";
   cout << "Pós-ordem: ";
   posordem(raiz);
   cout << "\n";
   cout << altura(raiz);
   cout << "\n";

   return 0;
}
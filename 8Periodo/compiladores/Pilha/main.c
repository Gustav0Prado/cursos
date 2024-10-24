#include "stack.h"

int main(){
  Pilha_t pilha;
  int a = 155;
  
  iniciaPilha(&pilha);

  inserePilha(&pilha, (void *)&a);

  printPilha(&pilha);

  desempilha(&pilha);
}

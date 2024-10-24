#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabsimb.h"

/*
   Inicia estrutura da TabSimb
*/
void iniciaTabSimb(TabSimb_t *tab){
   tab->top = NULL;
}

/*
   Tenta inserir um identificador de VS na TabSimb, retorna 0 caso sucesso e -1 caso falhe
*/
int insereTabSimbVS(char *ident, TabSimb_t *tab, int desloc, int nv, int tipo){
   if(ident && tab){
      Simb_t *newVar = malloc(sizeof(Simb_t));
      
      newVar->ident = malloc(sizeof(ident));
      strncpy(newVar->ident, ident, (int)sizeof(ident));

      newVar->next = tab->top;
      tab->top = newVar;

      newVar->deslocamento = desloc;
      newVar->nivel_lex = nv;
      newVar->uni.vs.tipo = tipo;

      return 0;
   }
   perror("Erro: Identificador ou TabSimb Nulos");
   return -1;
}

/*
   Tenta inserir um identificador de Procedimento na TabSimb, retorna 0 caso sucesso e -1 caso falhe
*/
int insereTabSimbProc(char *ident, TabSimb_t *tab, int rot, int nl){
   if(ident && tab){
      Simb_t *newVar = malloc(sizeof(Simb_t));
      
      newVar->ident = malloc(sizeof(ident));
      strncpy(newVar->ident, ident, (int)sizeof(ident));

      newVar->next = tab->top;
      tab->top = newVar;

      newVar->tipo = PROC;
      newVar->nivel_lex = nl;
      newVar->uni.proc.rotulo = rot;
      newVar->uni.proc.num_params = 0;
      newVar->uni.proc.tipo = PROC;

      return 0;
   }
   perror("Erro: Identificador ou TabSimb Nulos");
   return -1;
}


/*
   Insere funcao na tabela de simbolos
*/
int insereTabSimbFunc(char *ident, TabSimb_t *tab, int rot, int nl){
   if(ident && tab){
      Simb_t *newVar = malloc(sizeof(Simb_t));
      
      newVar->ident = malloc(sizeof(ident));
      strncpy(newVar->ident, ident, (int)sizeof(ident));

      newVar->next = tab->top;
      tab->top = newVar;

      newVar->tipo = PROC;
      newVar->nivel_lex = nl;
      newVar->uni.proc.rotulo = rot;
      newVar->uni.proc.num_params = 0;
      newVar->uni.proc.tipo = PROC_FUNCTION;

      return 0;
   }
   perror("Erro: Identificador ou TabSimb Nulos");
   return -1;
}


/*
   Tenta inserir um identificador de Procedimento na TabSimb, retorna 0 caso sucesso e -1 caso falhe
*/
int insereTabSimbParam(char *ident, TabSimb_t *tab, int pass, int nl, int desloc, int tipo){
   if(ident && tab){
      Simb_t *newVar = malloc(sizeof(Simb_t));
      
      newVar->ident = malloc(sizeof(ident));
      strncpy(newVar->ident, ident, (int)sizeof(ident));

      newVar->next = tab->top;
      tab->top = newVar;

      newVar->tipo = PFORM;
      newVar->uni.parform.passagem = pass;
      newVar->nivel_lex = nl;
      newVar->deslocamento = desloc;
      newVar->uni.parform.tipo = tipo;

      return 0;
   }
   perror("Erro: Identificador ou TabSimb Nulos");
   return -1;
}


/*
   Tenta label na tabela de simbolos
*/
int insereTabSimbLabel(char *ident, TabSimb_t *tab, int nl, int rot){
   if(tab){
      Simb_t *newVar = malloc(sizeof(Simb_t));
      
      newVar->ident = malloc(sizeof(ident));
      strncpy(newVar->ident, ident, (int)sizeof(ident));

      newVar->next = tab->top;
      tab->top = newVar;

      newVar->tipo = LABEL_;
      newVar->nivel_lex = nl;
      newVar->uni.label.rotulo = rot;

      return 0;
   }
   perror("Erro: TabSimb Nula");
   return -1;
}

/*
   Remove últimos n elementos da TabSimb e retorna 0 em caso de sucesso e -1 em caso de falha
*/
int removeNTabSimb(int n, TabSimb_t *tab){
   if(tab){
      if(tamanhoTabSimb(tab) < n){
         perror("Erro: Tentou remover mais elementos do que a TabSimb possui");
         return -1;
      }
      Simb_t *topo;
      for(int i = 0; i < n; ++i){
         topo = tab->top;

         tab->top = topo->next;

         free(topo->ident);
         topo->next = NULL;
         free(topo);
         topo = NULL;
      }
      return 0;
   }
   return -1;
}


/*
   Remove últimos n elementos da TabSimb e retorna 0 em caso de sucesso e -1 em caso de falha
*/
int removeTabSimb(Simb_t* simb, TabSimb_t *tab){
   if(tab && simb){
      Simb_t *aux;
      if(simb == tab->top){
         aux = tab->top;
         tab->top = aux->next;
         free(aux);
      }
      else{
         aux = tab->top;
         while(aux->next != simb && aux->next != NULL){
            aux = aux->next;
         }

         if(aux->next){
            aux->next = simb->next;
            free(simb);
         }
      }
      
      return 0;
   }
   return -1;
}


/*
   Remove últimos n elementos de nivel lexico nl da TabSimb e retorna 0 em caso de sucesso e -1 em caso de falha
*/
int removeNL(int nl, TabSimb_t *tab){
   if(tab){
      Simb_t *aux = tab->top;
      Simb_t *prox;
      int n = 0;
      
      while(aux != NULL && aux->nivel_lex > nl){
         prox = aux->next;
         if(aux->tipo != PROC && aux->tipo != LABEL_){
            removeTabSimb(aux, tab);
         }
         aux = prox;
      }

      return 0;
   }
   return -1;
}

/*
   Retorna atributos da variável buscada
*/
Simb_t *buscaTabSimb(char *ident, TabSimb_t *tab){
   if(tab && ident){
      Simb_t *aux = tab->top;
      while(aux != NULL){
         if(strcmp(ident, aux->ident) == 0){
            return aux;
         }
         else{
            aux = aux->next;
         }
      }
   }
  return NULL;
}


Simb_t* buscaTabSimbTipo(char *ident, TabSimb_t *tab, int tipo){
   if(tab && ident){
      Simb_t *aux = tab->top;
      while(aux != NULL){
         if(strcmp(ident, aux->ident) == 0 && aux->tipo == tipo){
            return aux;
         }
         else{
            aux = aux->next;
         }
      }
   }
  return NULL;
}

/*
   Desaloca estruturas da TabSimb
*/
int finalizaTabSimb(TabSimb_t *tab){
   if(tab){
      if(tab->top != NULL){
         perror("Erro: Tentou finalizar TabSimb não vazia");
         return -1;
      }
      else{
         free(tab);
         tab = NULL;
      }
   }
   return -1;
}

/*
   Printa elementos da TabSimb
*/
void printTabSimb(TabSimb_t *tab){
   if(tab){
      printf("----INICIO DA TabSimb----\n");
      Simb_t *aux = tab->top;
      while(aux != NULL){
         switch (aux->tipo){
         case VS:
            switch (aux->uni.vs.tipo){
               case INT:
                  printf("%s - VS - tipo: INTEGER - nv: %d, desloc: %d\n", aux->ident, aux->nivel_lex, aux->deslocamento);
                  break;

               case INDEF:
                  printf("%s - VS - tipo: INDEFINIDO\n", aux->ident);
                  break;
               
               default:
                  break;
            }
            break;
         
         case PROC:
            printf("%s - PROC - nl: %d - %d params\n", aux->ident, aux->nivel_lex, aux->uni.proc.num_params);
            break;
         
         case PFORM:
            switch (aux->uni.parform.passagem){
               case VALOR:
                  printf("%s - PARAM - tipo: VALOR - nl: %d, desloc: %d\n", aux->ident, aux->nivel_lex, aux->deslocamento);
                  break;

               case REF:
                  printf("%s - PARAM - tipo: REF   - nl: %d, desloc: %d\n", aux->ident, aux->nivel_lex, aux->deslocamento);
                  break;
               
               default:
                  break;
            }
            break;

         case LABEL_:
            printf("%s - LABEL - nl: %d, ROT: %02d\n", aux->ident, aux->nivel_lex, aux->uni.label.rotulo);
            break;
         
         default:
            break;
         }
         aux = aux->next;
      }
      printf("----FIM DA TabSimb----\n\n");
   }
}

/*
   Atualiza todos os tipos indefinidos de variaveis simples com
   com o tipo passado como parametro
*/
void atualizaTipos(TabSimb_t *tab, int tipo){
   if(tab){
      Simb_t *aux = tab->top;
      while(aux != NULL && aux->tipo == VS){
         if(aux->uni.vs.tipo == INDEF){
            aux->uni.vs.tipo = tipo;
         }
         aux = aux->next;
      }
   }
}


/*
   Atualiza valor de deslocamento dos parametros de um procedimento
*/
void atualizaParams(TabSimb_t *tab, Simb_t *procm, int tipo){
   int n = -4;
   Simb_t *top = tab->top;
   while(top->tipo == PFORM){
      top->deslocamento = n;
      top->uni.parform.tipo = tipo;
      n--;
      top = top->next;
   }
}


/*
   Atualiza tipo de retorno da funcao
*/
void atualizaFunc(TabSimb_t *tab, Simb_t *func, int tipo){
   while(func->tipo != PROC && func->uni.proc.tipo != PROC_FUNCTION){
      func = func->next;
   }
   func->uni.proc.retorno = INT;
}


/*
   Retorna tamanho da TabSimb
*/
int tamanhoTabSimb(TabSimb_t *tab){
   int cont = 0;
   if(tab){
      Simb_t *aux = tab->top;
      while(aux != NULL){
         cont++;
         aux = aux->next;
      }
   }

   return cont;
}

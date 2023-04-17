
// Testar se funciona corretamente o empilhamento de par�metros
// passados por valor ou por refer�ncia.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "compilador.h"
#include "stack.h"
#include "tabsimb.h"

int num_vars, desloc, nivel_lex = -1;
TabSimb_t tabela;
Pilha_t pilha_tipos;
Var_t *simb, *simb_aux;
char l_elem[1023];

char str[1024];
char* buildString(const char *fmt, ...) {
   va_list args;
   va_start(args, fmt);
   vsprintf(str, fmt, args);
   va_end(args);
   return str;

}

void checaTipos( char *cmd, int tipo ){
   int t1 = desempilha(&pilha_tipos);
   int t2 = desempilha(&pilha_tipos);
   if( t1 == tipo && t2 == tipo ){
      geraCodigo(NULL, cmd);
   }
   else{
      imprimeErro("TIPOS INCOMPATIVEIS NA OPERACAO\n");
   }
}

int confereAtribuicao( char *var ){
   int t1 = desempilha(&pilha_tipos);
   Var_t *simb_tipo = buscaTabSimb(var, &tabela);
   if(simb_tipo == NULL){
      imprimeErro(buildString("VARIAVEL \'%s\' NAO DECLARADA\n", var));
   }
   else if( t1 == simb_tipo->tipo ){
      geraCodigo(NULL, buildString("ARMZ %d, %d", nivel_lex, simb_tipo->deslocamento));
   }
   else{
      return 0;
   }
}

%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT NUM ATRIBUICAO
%token PROCEDURE FUNCTION GOTO
%token IF THEN ELSE
%token WHILE DO
%token ARRAY OF
%token LABEL TYPE
%token AND OR NOT
%token SOMA SUB MULT DIV
%token TRUE FALSE
%token READ WRITE

%%

programa    :{
            geraCodigo (NULL, "INPP");
            }
            PROGRAM IDENT
            ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
            bloco PONTO {
            geraCodigo(NULL, buildString("DMEM %d", num_vars));
            geraCodigo (NULL, "PARA");
            }
;

bloco       :
              parte_declara_vars
              {
              }

              comando_composto
              ;




parte_declara_vars:  var
;


var         : { desloc = 0; num_vars = 0; nivel_lex++; } VAR declara_vars{
               //Aloca todas as variáveis juntas
               geraCodigo(NULL, buildString("AMEM %d", num_vars));
               }
            |
;

declara_vars: declara_vars declara_var | declara_var
;

declara_var : lista_id_var DOIS_PONTOS
              tipo PONTO_E_VIRGULA
;

tipo        : IDENT
;

lista_id_var: lista_id_var VIRGULA IDENT { num_vars++; insereTabSimb(token, &tabela, desloc++); }
            | IDENT { num_vars++; insereTabSimb(token, &tabela, desloc++); }
;

lista_idents: lista_idents VIRGULA IDENT
            | IDENT
;

comando_composto: T_BEGIN comandos T_END

comandos:     comandos atribuicao | atribuicao
            | comandos leitura    | leitura
            | comandos escrita    | escrita
;

leitura: READ ABRE_PARENTESES lista_read FECHA_PARENTESES PONTO_E_VIRGULA
;

lista_read: lista_read VIRGULA IDENT {
            geraCodigo(NULL, "LEIT");
            simb = buscaTabSimb(token, &tabela);
            if(simb){
               geraCodigo(NULL, buildString("ARMZ %d, %d", nivel_lex, simb->deslocamento));
            }
            else{
               imprimeErro(buildString("VARIAVEL %s NAO DECLARADA", token));
            }
         }
         | IDENT {
            geraCodigo(NULL, "LEIT");
            simb = buscaTabSimb(token, &tabela);
            if(simb){
               geraCodigo(NULL, buildString("ARMZ %d, %d", nivel_lex, simb->deslocamento));
            }
            else{
               imprimeErro(buildString("VARIAVEL %s NAO DECLARADA", token));
            }
         }
;

escrita: WRITE ABRE_PARENTESES lista_write FECHA_PARENTESES PONTO_E_VIRGULA
;

lista_write: lista_write VIRGULA IDENT {
            simb = buscaTabSimb(token, &tabela);
            if(simb){
               geraCodigo(NULL, buildString("CRVL %d, %d", nivel_lex, simb->deslocamento));
               geraCodigo(NULL, "IMPR");
            }
            else{
               imprimeErro(buildString("VARIAVEL %s NAO DECLARADA", token));
            }
         }
         | IDENT {
            simb = buscaTabSimb(token, &tabela);
            if(simb){
               geraCodigo(NULL, buildString("CRVL %d, %d", nivel_lex, simb->deslocamento));
               geraCodigo(NULL, "IMPR");
            }
            else{
               imprimeErro(buildString("VARIAVEL %s NAO DECLARADA", token));
            }
         }
         | lista_write VIRGULA NUM {
            geraCodigo(NULL, buildString("CRCT %d", atoi(token)));
            geraCodigo(NULL, "IMPR");
         }
         | NUM {
            geraCodigo(NULL, buildString("CRCT %d", atoi(token)));
            geraCodigo(NULL, "IMPR");
         }
;

atribuicao: IDENT { strcpy(l_elem, token); } ATRIBUICAO expressao {
            confereAtribuicao(l_elem);
         } PONTO_E_VIRGULA
;

expressao: expressao SOMA termo {
            checaTipos("SOMA", INTEIRO);
         }
         | expressao SUB termo {
            checaTipos("SUBT", INTEIRO);
         }
         | expressao OR termo {
            checaTipos("DISJ", BOOLEANO);
         }
         | termo
;

termo:   termo MULT fator {
            checaTipos("MULT", INTEIRO);
         }
         | termo DIV fator {
            checaTipos("DIVI", INTEIRO);
         }
         | termo AND fator {
            checaTipos("CONJ", BOOLEANO);
         }
         | fator
;

fator:   NUM {
               // Atribui valor inteiro
               simb = buscaTabSimb(l_elem, &tabela);
               geraCodigo(NULL, buildString("CRCT %d", atoi(token)));

               empilha(&pilha_tipos, INTEIRO);
         }
         | IDENT {
               // Carrega valor de outra variavel
               simb = buscaTabSimb(l_elem, &tabela);
               simb_aux = buscaTabSimb(token, &tabela);
               geraCodigo(NULL, buildString("CRVL %d,%d", nivel_lex, simb_aux->deslocamento));

               empilha(&pilha_tipos, simb_aux->tipo);
         }
         | TRUE {
               geraCodigo(NULL, buildString("CRCT %d", 1));

               empilha(&pilha_tipos, BOOLEANO);
         }
         | FALSE {
               geraCodigo(NULL, buildString("CRCT %d", 0));

               empilha(&pilha_tipos, BOOLEANO);
         }
         | ABRE_PARENTESES expressao FECHA_PARENTESES

%%

int main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2) {
         printf("usage compilador <arq>a %d\n", argc);
         return(-1);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de S�mbolos
 * ------------------------------------------------------------------- */

   yyin=fp;
   yyparse();

   return 0;
}

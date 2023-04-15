
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
Var_t *simb, *simb_aux;
char l_elem[1023];

void geraCodArgs(char *rot, char * cmd, int a, int b, int num){
   char str[1024];
   if(num == 2){
      sprintf(str, cmd, a, b);
      geraCodigo(rot, str);
   }
   else if(num == 1){
      sprintf(str, cmd, a);
      geraCodigo(rot, str);
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
%token AND OR NOT DIV

%%

programa    :{
            geraCodigo (NULL, "INPP");
            }
            PROGRAM IDENT
            ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
            bloco PONTO {
            geraCodArgs(NULL, "DMEM %d", num_vars, 0, 1);
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
               geraCodArgs(NULL, "AMEM %d", num_vars, 0, 1);
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

comandos: comandos atribuicao | atribuicao
;

atribuicao: IDENT { strcpy(l_elem, token); } ATRIBUICAO expressao PONTO_E_VIRGULA
;

expressao: NUM {
               // Atribui valor inteiro
               simb = buscaTabSimb(l_elem, &tabela);
               geraCodArgs(NULL, "CRCT %d", atoi(token), 0, 1);
               geraCodArgs(NULL, "ARMZ %d,%d", nivel_lex, simb->deslocamento, 2);
               }
         | IDENT{
               // Carrega valor de outra variavel
               simb = buscaTabSimb(l_elem, &tabela);
               simb_aux = buscaTabSimb(token, &tabela);
               geraCodArgs(NULL, "CRVL %d,%d", nivel_lex, simb_aux->deslocamento, 2);
               geraCodArgs(NULL, "ARMZ %d,%d", nivel_lex, simb->deslocamento, 2);
               }

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

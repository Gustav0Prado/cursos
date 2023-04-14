
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

int num_vars, desloc;
TabSimb_t tabela;

void geraCodArgs(char *rot, char * cmd, int *a, int *b){
   char str[1024];
   if(a && b){
      sprintf(str, cmd, *a, *b);
      geraCodigo(rot, str);
   }
   else if(a && !b){
      sprintf(str, cmd, *a);
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
            geraCodArgs(NULL, "DMEM %d", &num_vars, NULL);
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


var         : { desloc = 0; num_vars = 0; } VAR declara_vars{
               //Aloca todas as variáveis juntas
               geraCodArgs(NULL, "AMEM %d", &num_vars, NULL);
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

lista_id_var: lista_id_var VIRGULA IDENT { num_vars++; }
            | IDENT { num_vars++; /*printf("%s\n", token); */}
;

lista_idents: lista_idents VIRGULA IDENT
            | IDENT
;

comando_composto: T_BEGIN comandos T_END

comandos: atribuicao | 
;

atribuicao: IDENT ATRIBUICAO NUM PONTO_E_VIRGULA
;

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

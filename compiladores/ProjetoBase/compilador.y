
// Testar se funciona corretamente o empilhamento de par�metros
// passados por valor ou por refer�ncia.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "compilador.h"
#include "pilha.h"
#include "tabsimb.h"

int num_vars, desloc, nivel_lex = -1, rot_atual = 0;
TabSimb_t tabela;
Pilha_t pilha_tipos, pilha_rotulos;
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

void checaTiposOP( char *cmd, int tipo ){
   int t1 = desempilha(&pilha_tipos);
   int t2 = desempilha(&pilha_tipos);

   if( t1 == tipo && t2 == tipo ){
      geraCodigo(NULL, cmd);
   }
   else{
      imprimeErro("TIPOS INCOMPATIVEIS NA OPERACAO\n");
   }
}

void checaTiposCMP( char *cmd){
   int t1 = desempilha(&pilha_tipos);
   int t2 = desempilha(&pilha_tipos);

   if( t1 == INTEIRO && t2 == INTEIRO ){
      geraCodigo(NULL, cmd);
   }
   else{
      imprimeErro("TIPOS INCOMPATIVEIS NA OPERACAO\n");
   }
}

void confereAtribuicao( char *var ){
   int t1 = desempilha(&pilha_tipos);
   Var_t *simb_tipo = buscaTabSimb(var, &tabela);

   if(simb_tipo == NULL){
      imprimeErro(buildString("VARIAVEL \'%s\' NAO DECLARADA\n", var));
   }
   else if( t1 == simb_tipo->tipo ){
      geraCodigo(NULL, buildString("ARMZ %d, %d", nivel_lex, simb_tipo->deslocamento));
   }
   else{
      imprimeErro("TIPOS INCOMPATIVEIS\n");
   }
}

void geraRotulo(int rot){
   geraCodigo(buildString("R%.2d", rot), "NADA");
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
%token MAIOR MAIOR_IGUAL MENOR MENOR_IGUAL IGUAL DESIGUAL

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

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

tipo        : IDENT {
            if( strcmp(token, "integer") == 0 ){
               atualizaTipos(&tabela, INTEIRO);
            }
            else if( strcmp(token, "boolean") == 0 ){
               atualizaTipos(&tabela, BOOLEANO);
            }
         }
;

lista_id_var: lista_id_var VIRGULA IDENT {
            num_vars++;
            insereTabSimb(token, &tabela, desloc++, INDEFINIDO);
         }
         | IDENT {
            num_vars++;
            insereTabSimb(token, &tabela, desloc++, INDEFINIDO);
         }
;

lista_idents: lista_idents VIRGULA IDENT
            | IDENT
;

comando_composto: T_BEGIN comandos T_END

comandos: comandos PONTO_E_VIRGULA comando | comando
;

comando: comando_vazio | comando_sem_rotulo
;

comando_vazio:;

comando_sem_rotulo: atribuicao
                  | leitura
                  | escrita
                  | repeticao
                  | condicional
                  | comando_composto
;

leitura: READ ABRE_PARENTESES lista_read FECHA_PARENTESES
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

escrita: WRITE ABRE_PARENTESES lista_write FECHA_PARENTESES
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
         }
;

expressao: expressao MAIOR expressao_simples {
            checaTiposCMP("CMMA");
            empilha(&pilha_tipos, BOOLEANO);
         }
         | expressao MAIOR_IGUAL expressao_simples{
            checaTiposCMP("CMAG");
            empilha(&pilha_tipos, BOOLEANO);
         }
         | expressao MENOR expressao_simples{
            checaTiposCMP("CMME");
            empilha(&pilha_tipos, BOOLEANO);
         }
         | expressao MENOR_IGUAL expressao_simples{
            checaTiposCMP("CMEG");
            empilha(&pilha_tipos, BOOLEANO);
         }
         | expressao IGUAL expressao_simples{
            checaTiposCMP("CMIG");
            empilha(&pilha_tipos, BOOLEANO);
         }
         | expressao DESIGUAL expressao_simples{
            checaTiposCMP("CMDG");
            empilha(&pilha_tipos, BOOLEANO);
         }
         | expressao_simples
;

expressao_simples: expressao_simples SOMA termo {
            checaTiposOP("SOMA", INTEIRO);
            empilha(&pilha_tipos, INTEIRO);
         }
         | expressao_simples SUB termo {
            checaTiposOP("SUBT", INTEIRO);
            empilha(&pilha_tipos, INTEIRO);
         }
         | expressao_simples OR termo {
            checaTiposOP("DISJ", BOOLEANO);
            empilha(&pilha_tipos, BOOLEANO);
         }
         | termo
;

termo:   termo MULT fator {
            checaTiposOP("MULT", INTEIRO);
            empilha(&pilha_tipos, INTEIRO);
         }
         | termo DIV fator {
            checaTiposOP("DIVI", INTEIRO);
            empilha(&pilha_tipos, INTEIRO);
         }
         | termo AND fator {
            checaTiposOP("CONJ", BOOLEANO);
            empilha(&pilha_tipos, BOOLEANO);
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
         | NOT fator {
               int tnot = desempilha(&pilha_tipos);
               if(tnot == BOOLEANO){
                  geraCodigo(NULL, "NEGA");
                  empilha(&pilha_tipos, BOOLEANO);
               }
               else{
                  imprimeErro("TIPOS INCOMPATIVEIS NA NEGACAO");
               }
         }
         | ABRE_PARENTESES expressao FECHA_PARENTESES

repeticao: WHILE {               
               empilha(&pilha_rotulos, rot_atual);
               geraRotulo(rot_atual);
               rot_atual++;
         } expressao DO{
               int tipo_exp = desempilha(&pilha_tipos);
               if(tipo_exp != BOOLEANO){
                  imprimeErro("EXPRESSAO NAO BOOLEANA");
               }
               empilha(&pilha_rotulos, rot_atual);
               geraCodigo(NULL, buildString("DSVF R%.2d", rot_atual));
               rot_atual++;
         } comando {
               int rot_saida  = desempilha(&pilha_rotulos);
               int rot_desvio = desempilha(&pilha_rotulos);
               geraCodigo(NULL, buildString("DSVS R%.2d", rot_desvio));
               geraRotulo(rot_saida);
         }
;

condicional: if_then %prec LOWER_THAN_ELSE {
               geraRotulo(rot_atual);
         }
         | if_then ELSE comando_sem_rotulo {
               geraRotulo(rot_atual);
         }
;

if_then: IF {
               empilha(&pilha_rotulos, rot_atual);
         }
         expressao {
               int tipo_exp = desempilha(&pilha_tipos);
               if(tipo_exp != BOOLEANO){
                  imprimeErro("EXPRESSAO NAO BOOLEANA");
               }
               int rot_desvio = desempilha(&pilha_rotulos);
               geraCodigo(NULL, buildString("DSVF R%.2d", rot_desvio));
               empilha(&pilha_rotulos, rot_desvio+1);
         }
         THEN comando_sem_rotulo {
               int rot_desvio = desempilha(&pilha_rotulos);
               geraCodigo(NULL, buildString("DSVS R%.2d", rot_desvio));
               geraRotulo(rot_atual);
               rot_atual++;
         }
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


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

int num_vars, desloc, nivel_lex = 0, rot_atual = 0;
TabSimb_t tabela;
Pilha_t pilha_tipos, pilha_rotulos;
Simb_t *simb, *simb_aux;
char l_elem[1023];
char str[1024];
char strAux[1024];
char l_proc[1023];

char* buildString(char *fmt, ...) {
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
   Simb_t *simb_tipo = buscaTabSimb(var, &tabela);

   if(simb_tipo == NULL){
      imprimeErro(buildString("VARIAVEL \'%s\' NAO DECLARADA\n", var));
   }
   else if( t1 == simb_tipo->uni.vs.tipo ){
      geraCodigo(NULL, buildString("ARMZ %d,%d", simb_tipo->uni.vs.nivel_lex, simb_tipo->uni.vs.deslocamento));
   }
   else{
      imprimeErro("TIPOS INCOMPATIVEIS\n");
   }
}

char *geraRotulo(int rot){
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

/* Esqueleto do programa */

programa :{
            geraCodigo (NULL, "INPP");
            }
            PROGRAM IDENT
            ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA bloco PONTO {
            geraCodigo(NULL, buildString("DMEM %d", num_vars));
            geraCodigo (NULL, "PARA");
            }
;

bloco :
              parte_declara_vars
              {
              }

            procs

              comando_composto
;

/* Declaracao de variaveis */

parte_declara_vars:  var
;


var         : { desloc = 0; num_vars = 0; /*nivel_lex++;*/ } VAR declara_vars{
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
            // else if( strcmp(token, "boolean") == 0 ){
            //    atualizaTipos(&tabela, BOOLEANO);
            // }
         }
;

lista_id_var: lista_id_var VIRGULA IDENT {
            num_vars++;
            insereTabSimbVS(token, &tabela, desloc++, nivel_lex, INDEFINIDO);
         }
         | IDENT {
            num_vars++;
            insereTabSimbVS(token, &tabela, desloc++, nivel_lex, INDEFINIDO);
         }
;

lista_idents: lista_idents VIRGULA IDENT
            | IDENT
;

/* Comandos */

comando_composto: T_BEGIN comandos T_END

comandos: comandos PONTO_E_VIRGULA comando | comando
;

comando: comando_vazio | comando_sem_rotulo
;

comando_vazio:;

comando_sem_rotulo: IDENT { strcpy(l_elem, token); } atribuicao_ou_proc
                  | leitura
                  | escrita
                  | repeticao
                  | condicional
                  | comando_composto
                  | chamaProc
;

/* leitura (read), escrita (write) e atribuicao */

leitura: READ ABRE_PARENTESES lista_read FECHA_PARENTESES
;

lista_read: lista_read VIRGULA IDENT {
            geraCodigo(NULL, "LEIT");
            simb = buscaTabSimb(token, &tabela);
            if(simb){
               geraCodigo(NULL, buildString("ARMZ %d,%d", simb->uni.vs.nivel_lex, simb->uni.vs.deslocamento));
            }
            else{
               imprimeErro(buildString("VARIAVEL %s NAO DECLARADA", token));
            }
         }
         | IDENT {
            geraCodigo(NULL, "LEIT");
            simb = buscaTabSimb(token, &tabela);
            if(simb){
               geraCodigo(NULL, buildString("ARMZ %d,%d", simb->uni.vs.nivel_lex, simb->uni.vs.deslocamento));
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
               geraCodigo(NULL, buildString("CRVL %d,%d", simb->uni.vs.nivel_lex, simb->uni.vs.deslocamento));
               geraCodigo(NULL, "IMPR");
            }
            else{
               imprimeErro(buildString("VARIAVEL %s NAO DECLARADA", token));
            }
         }
         | IDENT {
            simb = buscaTabSimb(token, &tabela);
            if(simb){
               geraCodigo(NULL, buildString("CRVL %d,%d", simb->uni.vs.nivel_lex, simb->uni.vs.deslocamento));
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

atribuicao_ou_proc: ATRIBUICAO expressao { confereAtribuicao(l_elem); } | chamaProc
;

/* Expressoes matematicas */

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
               geraCodigo(NULL, buildString("CRVL %d,%d", simb_aux->uni.vs.nivel_lex, simb_aux->uni.vs.deslocamento));

               empilha(&pilha_tipos, simb_aux->uni.vs.tipo);
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


/* Comando repetitivo (while) */

repeticao: WHILE {               
               empilha(&pilha_rotulos, rot_atual);
               printPilha(&pilha_rotulos);
               geraRotulo(rot_atual);
               rot_atual++;
         } expressao DO{
               int tipo_exp = desempilha(&pilha_tipos);
               if(tipo_exp != BOOLEANO){
                  imprimeErro("EXPRESSAO NAO BOOLEANA");
               }
               empilha(&pilha_rotulos, rot_atual);
               printPilha(&pilha_rotulos);
               geraCodigo(NULL, buildString("DSVF R%.2d", rot_atual));
               rot_atual++;
         } comando {
               printPilha(&pilha_rotulos);
               int rot_saida  = desempilha(&pilha_rotulos);
               int rot_desvio = desempilha(&pilha_rotulos);
               geraCodigo(NULL, buildString("DSVS R%.2d", rot_desvio));
               geraRotulo(rot_saida);
         }
;

/* Comandos condicionais (if) */

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

/* Procedimentos (Procedures) */
procs: proc procs | proc

proc: PROCEDURE {
               nivel_lex++;
               empilha(&pilha_rotulos, rot_atual+1);
               empilha(&pilha_rotulos, rot_atual);
               geraCodigo(NULL, buildString("DSVS R%.2d", rot_atual));
               rot_atual++;
         }
      IDENT {
               strcpy(strAux, buildString("R%.2d", rot_atual)); 
               geraCodigo(strAux, buildString("ENPR %d", nivel_lex));
               rot_atual++;
         }
      PONTO_E_VIRGULA blocoPF | 

blocoPF: parte_declara_vars comando_composto PONTO_E_VIRGULA { 
               nivel_lex--;

               geraCodigo(NULL, buildString("DMEM %d", num_vars));
               geraCodigo(NULL, buildString("RTPR %d,%d", 1, 0));

               int rot_desvio = desempilha(&pilha_rotulos);
               geraCodigo(buildString("R%.2d", rot_desvio), "NADA");
         }

chamaProc: {
               int rot_desvio = desempilha(&pilha_rotulos);
               geraCodigo(NULL, buildString("CHPR R%.2d,%d", rot_desvio, nivel_lex));
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

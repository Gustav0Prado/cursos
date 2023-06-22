
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

int num_vars, desloc, nivel_lex = 0, rot_atual = 0, n_params, paramPassados,
tipo_param, entra_proc = 0, num_vars_total = 0;
TabSimb_t tabela;
Pilha_t pilha_tipos, pilha_rotulos, pilha_vars;
Simb_t *simb, *simb_aux;
char l_elem[1023];
char atrib[1023];
char func_i[1023];
char str[1024];
char strAux[1024];
Simb_t *proc;

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
   // Variavel simples
   else if( (simb_tipo->tipo == VS && t1 == simb_tipo->uni.vs.tipo) ){
      geraCodigo(NULL, buildString("ARMZ %d, %d", simb_tipo->nivel_lex, simb_tipo->deslocamento));
   }
   // Parametro formal
   else if( (simb_tipo->tipo == PFORM && t1 == simb_tipo->uni.parform.tipo)){
      if( simb_tipo->uni.parform.passagem == VALOR){
         geraCodigo(NULL, buildString("ARMZ %d, %d", simb_tipo->nivel_lex, simb_tipo->deslocamento));
      }
      else{
         geraCodigo(NULL, buildString("ARMI %d, %d", simb_tipo->nivel_lex, simb_tipo->deslocamento));
      }
   }
   else{
      imprimeErro("TIPOS INCOMPATIVEIS\n");
   }
}

char *geraRotulo(int rot){
   geraCodigo(buildString("R%.2d", rot), "NADA");
   rot_atual++;
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

%nonassoc NADA
%nonassoc ABRE_PARENTESES

%%

//---------------------------------------------------------------- Esqueleto do Programa -------------------------------------------------------------------------------------//

programa :{
               geraCodigo (NULL, "INPP");
            }
            PROGRAM IDENT
            ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA bloco  PONTO {
               int vars = desempilha(&pilha_vars);
               geraCodigo(NULL, buildString("DMEM %d", vars));
               geraCodigo (NULL, "PARA");
            }
;

bloco :
         parte_declara_vars
         {geraCodigo(NULL, buildString("DSVS R%02d", rot_atual)); empilha(&pilha_rotulos, rot_atual);} 

         

         parte_declara_procs

         {int rot_desvio = desempilha(&pilha_rotulos); geraCodigo(buildString("R%.2d", rot_desvio), "NADA"); rot_atual++;}
         comando_composto
;

//---------------------------------------------------------------- Declaração de variáveis -------------------------------------------------------------------------------------//

parte_declara_vars:  var
;


var         : { desloc = 0; num_vars_total = 0; } VAR declara_vars { empilha(&pilha_vars, num_vars_total); } |  %empty { empilha(&pilha_vars, 0); } //Sem vars
;

declara_vars: declara_vars {num_vars = 0;} declara_var | {num_vars = 0;} declara_var
;

declara_var : lista_id_var DOIS_PONTOS
              tipo PONTO_E_VIRGULA {
                  geraCodigo(NULL, buildString("AMEM %d", num_vars));
                  num_vars_total += num_vars;
              }
;

tipo        : IDENT {
            if( strcmp(token, "integer") == 0 ){
               atualizaTipos(&tabela, INTEIRO);
            }
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

//---------------------------------------------------------------- Comandos -------------------------------------------------------------------------------------//

comando_composto: T_BEGIN comandos T_END

comandos: comandos PONTO_E_VIRGULA comando | comando
;

comando: comando_vazio | comando_sem_rotulo
;

comando_vazio: %empty ;

comando_sem_rotulo: IDENT { strcpy(l_elem, token); } atribuicao_ou_proc
                  | leitura
                  | escrita
                  | repeticao
                  | condicional
                  | comando_composto
;

//---------------------------------------------------------------- Leitura, Escrita, Atribuição -------------------------------------------------------------------------------------//

leitura: READ ABRE_PARENTESES lista_read FECHA_PARENTESES
;

lista_read: lista_read VIRGULA IDENT {
            geraCodigo(NULL, "LEIT");
            simb = buscaTabSimb(token, &tabela);
            if(simb){
               if( (simb->tipo == VS) || (simb->uni.parform.passagem == VALOR)){
                  geraCodigo(NULL, buildString("ARMZ %d, %d", simb->nivel_lex, simb->deslocamento));
               }
               else{
                  geraCodigo(NULL, buildString("ARMI %d, %d", simb->nivel_lex, simb->deslocamento));
               }
            }
            else{
               imprimeErro(buildString("VARIAVEL %s NAO DECLARADA", token));
            }
         }
         | IDENT {
            geraCodigo(NULL, "LEIT");
            simb = buscaTabSimb(token, &tabela);
            if(simb){
               if( (simb->tipo == VS) || (simb->uni.parform.passagem == VALOR)){
                  geraCodigo(NULL, buildString("ARMZ %d, %d", simb->nivel_lex, simb->deslocamento));
               }
               else{
                  geraCodigo(NULL, buildString("ARMI %d, %d", simb->nivel_lex, simb->deslocamento));
               }
            }
            else{
               imprimeErro(buildString("VARIAVEL %s NAO DECLARADA", token));
            }
         }
;

escrita: WRITE ABRE_PARENTESES lista_write FECHA_PARENTESES
;

lista_write: lista_write VIRGULA expressao {geraCodigo(NULL, "IMPR");} | expressao {geraCodigo(NULL, "IMPR");}
;

atribuicao_ou_proc: ATRIBUICAO expressao { confereAtribuicao(l_elem); } | chamaProc { strcpy(l_elem, token); }
;

//---------------------------------------------------------------- Expressões Matemáticas -------------------------------------------------------------------------------------//

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
         | IDENT {strcpy(atrib, token); } atribui

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


//---------------------------------------------------------------- Comandos repetitivos (while) -------------------------------------------------------------------------------------//

repeticao: WHILE {
               empilha(&pilha_rotulos, rot_atual);
               geraRotulo(rot_atual);
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

//---------------------------------------------------------------- Comandos condicionais (if) -------------------------------------------------------------------------------------//

condicional: if_then %prec LOWER_THAN_ELSE {
               int rot_desvio = desempilha(&pilha_rotulos);
               geraCodigo(buildString("R%.2d", rot_desvio), "NADA");
         }
         | if_then ELSE comando_sem_rotulo {
               int rot_desvio = desempilha(&pilha_rotulos);
               geraCodigo(buildString("R%.2d", rot_desvio), "NADA");
         }
;

if_then: IF {
               rot_atual++;
               empilha(&pilha_rotulos, rot_atual+1);
         }
         expressao {
               int tipo_exp = desempilha(&pilha_tipos);
               if(tipo_exp != BOOLEANO){
                  imprimeErro("EXPRESSAO NAO BOOLEANA");
               }
               int rot_desvio = desempilha(&pilha_rotulos);
               geraCodigo(NULL, buildString("DSVF R%.2d", rot_desvio));
               empilha(&pilha_rotulos, rot_atual);
         }
         THEN comando_sem_rotulo {
               int rot_desvio = desempilha(&pilha_rotulos);
               geraCodigo(NULL, buildString("DSVS R%.2d", rot_desvio));
               empilha(&pilha_rotulos, rot_atual);
               geraRotulo(rot_atual+1);
         }
;

//---------------------------------------------------------------- Procedimentos (Procedures) -------------------------------------------------------------------------------------//

// Parte de declaracao de todas as procs
parte_declara_procs: declara_procs | declara_funcs | comando_vazio


// Declaracao das procs do programa
declara_procs: declara_procs declara_proc | declara_proc


// Declaracao da procedure => PROCEDURE IDENT paramsFormais ; blocoPF
declara_proc: PROCEDURE {
               nivel_lex++;
         }
           IDENT {
               rot_atual++;
               insereTabSimbProc(token, &tabela, rot_atual, nivel_lex);
               proc = buscaTabSimb(token, &tabela);
               strcpy(strAux, buildString("R%.2d", rot_atual));
               geraCodigo(strAux, buildString("ENPR %d", nivel_lex));
         } paramsFormais PONTO_E_VIRGULA blocoPF { removeNL(nivel_lex, &tabela);}


// Parametros formais do proc => (listaParamsForms)
paramsFormais: ABRE_PARENTESES listaParamsForms FECHA_PARENTESES | %empty  


// Declaracao dos params do proc =>  [listaParamsForms;] declaraParams
listaParamsForms: listaParamsForms PONTO_E_VIRGULA declaraParams | declaraParams


//Regra de declaracao de parametros => declaraParam : integer  |  var declaraParam : integer
declaraParams: { tipo_param = VALOR; } declaraParam DOIS_PONTOS tipoParam | VAR { tipo_param = REF; } declaraParam DOIS_PONTOS tipoParam


// Declaracao de params do mesmo tipo => a,b,c
declaraParam: declaraParam VIRGULA IDENT {
               proc->uni.proc.passagem[proc->uni.proc.num_params] = tipo_param;
               proc->uni.proc.num_params++;
               insereTabSimbParam(token, &tabela, tipo_param, nivel_lex, proc->uni.proc.num_params, INDEFINIDO);
         } | IDENT {
               proc->uni.proc.passagem[proc->uni.proc.num_params] = tipo_param;
               proc->uni.proc.num_params++;
               insereTabSimbParam(token, &tabela, tipo_param, nivel_lex, proc->uni.proc.num_params, INDEFINIDO);
         }


// Declaracao do tipo do Parametro formal
tipoParam: IDENT {
               if( strcmp(token, "integer") == 0 ){
                  atualizaParams(&tabela, proc, INTEIRO);
               }
         }


// Begin e end de dentro do proc
blocoPF: parte_declara_vars { rot_atual++; geraCodigo(NULL, buildString("DSVS R%02d", rot_atual)); empilha(&pilha_rotulos, rot_atual); }  
         parte_declara_procs {int rot_desvio = desempilha(&pilha_rotulos); geraCodigo(buildString("R%.2d", rot_desvio), "NADA");}
         comando_composto { 
               int vars = desempilha(&pilha_vars);
               if(vars > 0){
                  geraCodigo(NULL, buildString("DMEM %d", vars));
               }
               geraCodigo(NULL, buildString("RTPR %d, %d", nivel_lex, proc->uni.proc.num_params));
               nivel_lex--;
         } PONTO_E_VIRGULA


// Chamada de procedimento => p(x)
chamaProc: chamaProcParams {
               simb = buscaTabSimb(l_elem, &tabela);
               if(simb && simb->tipo == PROC){
                  geraCodigo(NULL, buildString("CHPR R%.2d, %d", simb->uni.proc.rotulo, nivel_lex));
                  n_params = simb->uni.proc.num_params;
               }
               else{
                  imprimeErro(buildString("Procedimento %s não declarado", l_elem));
               }
         }


chamaProcParams: paramsProc | %empty


// Parenteses e checagem de paramatros de um proc => ( listaParams )
paramsProc: ABRE_PARENTESES { paramPassados = 0;} listaParams FECHA_PARENTESES {
               if(paramPassados != proc->uni.proc.num_params){
                  imprimeErro("N° de parametros invalido para esse procedimento\n");
               }
         } 


// Lista de params de um proc => a,b,c
listaParams: listaParams VIRGULA { entra_proc = 1; } expressao { paramPassados++; entra_proc = 0; } | { entra_proc = 1; } expressao { paramPassados++; entra_proc = 0; }


//---------------------------------------------------------------- Funções -------------------------------------------------------------------------------------//
// Declaracao das procs do programa
declara_funcs: declara_funcs declara_func | declara_func


// Declaracao da procedure => PROCEDURE IDENT paramsFormais ; blocoPF
declara_func: FUNCTION {
               nivel_lex++;
         }
           IDENT {
               rot_atual++;
               insereTabSimbProc(token, &tabela, rot_atual, nivel_lex);
               proc = buscaTabSimb(token, &tabela);
               strcpy(strAux, buildString("R%.2d", rot_atual));
               geraCodigo(strAux, buildString("ENPR %d", nivel_lex));
         } paramsFormais DOIS_PONTOS tipoFunc PONTO_E_VIRGULA blocoPF { removeNL(nivel_lex, &tabela);}

tipoFunc: IDENT {
               if( strcmp(token, "integer") == 0 ){
                  atualizaFunc(&tabela, proc, INTEIRO);
                  insereTabSimbVS(proc->ident, &tabela, -4-proc->uni.proc.num_params, nivel_lex, INTEIRO);
               }
         }


atribui:  {geraCodigo(NULL, "AMEM 1"); strcpy(func_i, atrib); } paramsProc {
               simb = buscaTabSimbTipo(func_i, &tabela, PROC);
               if(simb && simb->tipo == PROC){
                  geraCodigo(NULL, buildString("CHPR R%.2d, %d", simb->uni.proc.rotulo, simb->nivel_lex));
                  n_params = simb->uni.proc.num_params;
               }
               else{
                  printTabSimb(&tabela);
                  imprimeErro(buildString("Funcao '%s' não declarada", func_i));
               }
               empilha(&pilha_tipos, simb->uni.proc.retorno);
         }
         | %empty {
               // Carrega valor de outra variavel
               simb_aux = buscaTabSimb(atrib, &tabela);
               if(!entra_proc && simb_aux){
                  switch(simb_aux->tipo){
                     case VS:
                        geraCodigo(NULL, buildString("CRVL %d, %d", simb_aux->nivel_lex, simb_aux->deslocamento));
                        empilha(&pilha_tipos, simb_aux->uni.vs.tipo);
                        break;

                     case PFORM:
                        if(simb_aux->uni.parform.passagem == VALOR){
                           geraCodigo(NULL, buildString("CRVL %d, %d", simb_aux->nivel_lex, simb_aux->deslocamento));
                        }
                        else{
                           geraCodigo(NULL, buildString("CRVI %d, %d", simb_aux->nivel_lex, simb_aux->deslocamento));
                        }
                        empilha(&pilha_tipos, simb_aux->uni.parform.tipo);
                        break;

                     case PROC:
                        geraCodigo(NULL, "AMEM 1");
                        geraCodigo(NULL, buildString("CHPR R%.2d, %d", simb_aux->uni.proc.rotulo, simb_aux->nivel_lex));
                        empilha(&pilha_tipos, simb_aux->uni.proc.retorno);
                        break;

                     default:
                        break;
                  }
               }
               // Caso esteja declarando procedimento, checa tipos de passagem dos parametros
               else if(entra_proc){
                  if(proc->uni.proc.passagem[paramPassados] == VALOR  || simb_aux->uni.parform.passagem == REF){
                     geraCodigo(NULL, buildString("CRVL %d, %d", simb_aux->nivel_lex, simb_aux->deslocamento));
                  }
                  else{
                     geraCodigo(NULL, buildString("CREN %d, %d", simb_aux->nivel_lex, simb_aux->deslocamento));
                  }
                  empilha(&pilha_tipos, simb_aux->uni.parform.tipo);
               }
               else{
                  imprimeErro(buildString("VARIAVEL %s NAO DECLARADA", token));
               }
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

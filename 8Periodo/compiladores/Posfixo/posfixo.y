
%{
#include <stdio.h>
#include "compiladorF.h"
%}

%token IDENT MAIS MENOS AND OR ASTERISCO DIV ABRE_PARENTESES FECHA_PARENTESES

%%

expr       : expr MAIS termo {printf ("+"); } |
             expr MENOS termo {printf ("-"); } | 
             expr OR termo { printf (" OR "); } | 
             termo
;

termo      : termo ASTERISCO fator  {printf ("*"); }| 
             termo DIV fator  {printf ("/"); }|
             termo AND fator  {printf (" AND "); }|
             fator
;

fator      : IDENT {printf ("%s", token); } | ABRE_PARENTESES expr FECHA_PARENTESES
;

%%

int main (int argc, char** argv) {
   yyparse();
   printf("\n");
}


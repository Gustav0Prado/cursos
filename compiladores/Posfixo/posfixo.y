
%{
#include <stdio.h>
int yylex();
%}

%token IDENT MAIS MENOS AND OR ASTERISCO DIV ABRE_PARENTESES FECHA_PARENTESES

%%

expr       : expr MAIS termo {printf ("+"); } |
             expr MENOS termo {printf ("-"); } |
             termo
;

termo      : termo ASTERISCO fator  {printf ("*"); }| 
             termo DIV fator  {printf ("/"); }|
             fator
;

fator      : IDENT {
   if(yylval == 0){
      printf ("A");
   }
   else{
      printf ("B");
   }
}
;

%%

int main (int argc, char** argv) {
   yyparse();
   printf("\n");
}


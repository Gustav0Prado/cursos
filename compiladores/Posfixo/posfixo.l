%{
#include "posfixo.tab.h"
#include "compiladorF.h"
#include<string.h>
%}

%%

[\n\t ]  

\+    { return MAIS; }
\-    { return MENOS; }
\*    { return ASTERISCO; }
\/    { return DIV;  }
and   { return AND; }
or    { return OR; }
\(    { return ABRE_PARENTESES; }
\)    { return FECHA_PARENTESES; }
a     { 
         return IDENT;
         strncpy (token, yytext, 256);
      }
b     { 
         return IDENT;
         strncpy (token, yytext, 256);
      }

%%


%{
#include "posfixo.tab.h"
%}

%%

[\n\t ]  

\+    { return MAIS; }
\-    { return MENOS; }
\*    { return ASTERISCO;  }
\/    { return DIV;  }
a     { 
   yylval = 0;
   return IDENT; }
b     { 
   yylval = 1;
   return IDENT; }
and   { return AND; }
or   { return OR; }

%%


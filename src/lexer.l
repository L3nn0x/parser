%{
#include <lexer.h>
#include "parser.h"
#include <stdio.h>

  void yyerror (char *s) {
    fprintf (stderr, "%s\n", s);
  }
  
%}

%%

[[:digit:]]*("."[[:digit:]]*)? {yylval.number = atof(yytext); return NUMBER;}

";" return END_EXPR;

"+" return PLUS;
"-" return MINUS;
"*" return TIMES;
"/" return DIV;

[()] return yytext[0];

. {yyerror("unexpected character error");}

%%

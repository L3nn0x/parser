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

"<-" return ASSIGN;

[()] return yytext[0];

[_[:alpha:]]+ {yylval.id = strdup(yytext); return ID;}

[[:space:]] {}

. {yyerror("unexpected character error");}

%%

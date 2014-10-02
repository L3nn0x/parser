%{
#include <lexer.h>
#include <stdio.h>
#include <stdlib.h>
%}
									
%union {
	double number;
	char *id;
}

%token <number> NUMBER
%token <id> ID
%token END_EXPR MINUS PLUS TIMES DIV

%left MINUS PLUS
%left TIMES DIV

%type <number> e

%%

s:
		s e END_EXPR {printf("%f\n", $2);}
	|	s END_EXPR {}
	|	error END_EXPR {yyerror("syntax error");}
	|	/*EMPTY WORD*/
		;

e:		NUMBER {$$ = $1;}
	|	e PLUS e {$$ = $1 + $3;}
	|	e MINUS e {$$ = $1 - $3;}
	|	e TIMES e {$$ = $1 * $3;}
	|	e DIV e {if ($3) $$ = $1 / $3; else {$$=0; yyerror("null division error");}}
	|	MINUS e {$$ = 0 - $2;}
	|	PLUS e {$$ = $2;}
	|	'(' e ')' {$$ = $2;}
	|	ID {printf("ID : %s\n", $1); free($1);$$=0;}
	;

%%

int main(void)
{
    yyparse();
    return EXIT_SUCCESS;
}

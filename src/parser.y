%{
#include <lexer.h>
#include <variables.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}
									
%union {
	double number;
	char *id;
}

%token <number> NUMBER
%token <id> ID
%token END_EXPR MINUS PLUS TIMES DIV ASSIGN

%left ASSIGN
%left MINUS PLUS
%left TIMES DIV

%type <number> e

%%

s:
		s e END_EXPR {printf("%f\n", $2);}
	|	s error END_EXPR {yyerror("syntax error");}
	|	s ID ASSIGN ID END_EXPR {
		  if(!strcmp($2, $4)) 
		    del_variable($2);
		  else 
		    add_variable($2, get_variable($4));
		}
	|	s ID ASSIGN e END_EXPR {add_variable($2, $4);}
	|	/*EMPTY WORD*/
	;

e:		NUMBER {$$ = $1;}
	|	e PLUS e {$$ = $1 + $3;}
	|	e MINUS e {$$ = $1 - $3;}
	|	e TIMES e {$$ = $1 * $3;}
	|	e DIV e {
		if ($3) 
		    $$ = $1 / $3; 
		else {
		    $$=0; 
		    yyerror("null division error");
		}}
	|	MINUS e {$$ = 0 - $2;}
	|	PLUS e {$$ = $2;}
	|	'(' e ')' {$$ = $2;}
	|	ID {
		if(is_defined_variable($1))
		    $$ = get_variable($1);
		else{
		    yyerror("undefined variable error");
		    $$ = 0;
		}}
	;

%%

int main(void)
{
    yyparse();
    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include "lexical.h"

int	main(int argc, char **argv)
{
	init_lexical();
	while (1)
	{
		t_symbol *tmp = get_next_symbol();
		if (!tmp)
			continue ;
		printf("symbol : %s$ : \n", tmp->entry);
		printf("type : %s\n", tmp->type ? tmp->type == ID ? "ID" : "VALUE" : "KEYWORD");
		if (tmp->value)
			printf("value : %d\n", *(int *)tmp->value);
	}
	return (0);
}

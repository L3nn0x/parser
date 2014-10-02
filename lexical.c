#include <stdlib.h>
#include "lexical.h"

#include <stdio.h>
#include "string.h"

static t_config	*g_config;

void		init_lexical(void)
{
	int	i;

	g_config = (t_config *)malloc(sizeof(*g_config));
	g_config->root = 0;
	g_config->regexp_pass = (char **)malloc(sizeof(char **));
	g_config->regexp_pass[0] = " *\t*";
	g_config->keywords = "+-*/";
	i = -1;
	while (++i < SIZE)
		g_config->buffer[i] = 0;
}

static t_symbol	*add_elem(t_symbol **s)
{
	t_list	*cursor;
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(*tmp));
	tmp->symbol = *s;
	tmp->next = 0;
	if (!g_config->root)
	{
		g_config->root = tmp;
		return (*s);
	}
	cursor = g_config->root;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = tmp;
	return (*s);
}

static int	regexp_match(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] && (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n'))
		++i;
	return (i);
}

static int	get_next_block(void)
{
	return (fgets(g_config->buffer, SIZE, stdin) != 0);
}

t_symbol	*get_next_symbol(void)
{
	t_symbol	*tmp;
	int			i;
	int			j;
	int			k;

	tmp = (t_symbol *)malloc(sizeof(*tmp));
	i = 0;
	tmp->entry = 0;
	tmp->value = 0;
	i += regexp_match(&g_config->buffer[i]);
	while (i >= SIZE || !g_config->buffer[i])
	{
		if (!get_next_block())
			return (0);
		i = 0;
		i += regexp_match(&g_config->buffer[i]);
	}
	j = -1;
	while (++j < 4)
	{
		if (g_config->buffer[i] == g_config->keywords[j])
		{
			tmp->type = KEYWORD;
			j = g_config->buffer[i + 1];
			g_config->buffer[i + 1] = 0;
			tmp->entry = strdup(&g_config->buffer[i]);
			g_config->buffer[i + 1] = j;
			tmp = add_elem(&tmp);
			i++;
			memcpy(g_config->buffer, &g_config->buffer[i], SIZE - i);
			return (tmp);
		}
	}
	if (g_config->buffer[i] >= '0' && g_config->buffer[i] <= '9')
	{
		tmp->type = VALUE;
		tmp->entry = strdup(&g_config->buffer[i]);
		tmp->type_value = sizeof(int);
		tmp->value = malloc(tmp->type_value);
		*(int *)tmp->value = atoi(&g_config->buffer[i]);
		j = 0;
		while (tmp->entry[j] >= '0' && tmp->entry[j] <= '9')
			++j;
		tmp->entry[j] = 0;
		i += j;
		tmp = add_elem(&tmp);
		memcpy(g_config->buffer, &g_config->buffer[i], SIZE - i);
		return (tmp);
	}
	tmp->type = ID;
	tmp->entry = strdup(&g_config->buffer[i]);
	j = 0;
	while (tmp->entry[j] && tmp->entry[j] != ' ' && tmp->entry[j] != '\t' && tmp->entry[j] != '\n')
	{
		k = -1;
		while (++k < 4)
			if (tmp->entry[j] == g_config->keywords[k])
				break ;
		if (k != 4)
			break ;
		++j;
	}
	tmp->entry[j] = 0;
	tmp = add_elem(&tmp);
	i += j;
	memcpy(g_config->buffer, &g_config->buffer[i], SIZE - i);
	return (tmp);
}

#ifndef LEXICAL_H
# define LEXICAL_H

# define KEYWORD 0
# define VALUE 1
# define ID 2

# define SIZE 64

typedef struct	s_symbol
{
	char	*entry;
	int		type;
	int		type_value;
	void	*value;
}				t_symbol;

typedef struct	s_list
{
	t_symbol		*symbol;
	struct s_list	*next;
}				t_list;

typedef struct	s_config
{
	t_list	*root;
	char	**regexp_pass;
	char	*keywords;
	char	buffer[SIZE];
}				t_config;

void		init_lexical(void);
t_symbol	*get_next_symbol(void);

#endif /* !LEXICAL_H */

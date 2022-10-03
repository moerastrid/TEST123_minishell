#include "../../minishell.h"

// Totally illegal
void	print_token_type(enum e_token_type num)
{
	switch (num)
	{
		case 0:
			printf("%s", "WORD");
		break ;
		case 1:
			printf("%s", "GREAT");
		break ;
		case 2:
			printf("%s", "LESS");
		break ;
		case 3:
			printf("%s", "PIPE");
		break ;
		case 4:
			printf("%s", "GREATGREAT");
		break ;
		case 5:
			printf("%s", "LESSLESS");
		break ;
		case 6:
			printf("%s", "DOLL");
		break ;
		case 7:
			printf("%s", "DOLLQ");
		break ;
		case 8:
			printf("%s", "QUOT");
		break ;
		case 9:
			printf("%s", "DQUOT");
		break ;
	}
}

void	print_tokens(t_token *root)
{
	t_token	*i;

	i = root;
	printf("Token list:\t\t");
	while (i != NULL)
	{
		printf("[");
		print_token_type(i->type);
		printf(", %s]", i->data);
		i = i->next;
		if (i != NULL)
			printf("->");
	}
	printf("\n");
}

void	print_str_list(t_str_list *root, int mode)
{
	t_str_list	*i;

	i = root;
	if (mode == 0)
		printf("Infile list:\t\t");
	if (mode == 1)
		printf("Outfile list:\t\t");
	if (mode == 2)
		printf("Delimiter list:\t\t");
	while (i != NULL)
	{
		printf("[%s]", i->str);
		i = i->next;
		if (i != NULL)
			printf("->");
	}
	printf("\n");
}

void	print_simples(t_cmd *cmd)
{
	t_simple	*simple;
	char		**argv;
	int			i;

	simple = cmd->simples;
	while (simple != NULL)
	{
		argv = simple->argv;
		printf("Simple {bin:%s, argv:[", simple->bin);
		i = 0;
		while (i < simple->argc)
		{
			if (i + 1 == simple->argc)
				printf("%s", argv[i++]);
			else
				printf("%s, ", argv[i++]);
		}
		simple = simple->next;
		printf("]}\n");
	}
}

// How will this ever end? Suggestion: Change children global to struct containing also the size of array
void print_children(pid_t *pids)
{
	while (*pids)
	{

	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 16:54:53 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/27 22:24:00 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void cmd_setup(t_cmd *cmd)
{
	cmd->amount_cmd = 0;
	cmd->simples = NULL;
	cmd->outfile = NULL;
	cmd->infile = NULL;
	cmd->errfile = NULL;
}

static void print_token_type(enum e_token_type num)
{
	switch (num) {
		case 0:
			printf("%s", "WORD");
			break;
		case 1:
			printf("%s", "GREAT");
			break;
		case 2:
			printf("%s", "LESS");
			break;
		case 3:
			printf("%s", "PIPE");
			break;
		case 4:
			printf("%s", "GREATGREAT");
			break;
		case 5:
			printf("%s", "LESSLESS");
			break;
		case 6:
			printf("%s", "DOLL");
			break;
		case 7:
			printf("%s", "DOLLQ");
			break;
	}
}

static void print_tokens(t_token *root)
{
	t_token	*i;

	i = root;
	printf("Token list:\n");
	while(i != NULL)
	{
		printf("[");
		print_token_type(i->type);
		printf(" , %s", i->data);
		i = i->next;
		printf("] -> ");
	}
	printf("\n");
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_cmd	cmd;

	cmd_setup(&cmd);
	line = NULL;
	while (1)
	{
		line = prompt();
		if (!line)
			return (1);
		if (*line)
		{
			tokens = tokenize(line);
			if(tokens == NULL)
			{
				printf("%s\n", NULL);
				return (1);
			}
			print_tokens(tokens);
			parse(tokens, &cmd, envp);
			execute(cmd);
		}
		free(line);
		line = NULL;
	}
	rl_clear_history();
	return (0);
}

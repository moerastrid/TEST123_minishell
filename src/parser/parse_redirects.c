/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_redirects.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:29:17 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 22:29:18 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../../minishell.h"

static void	simple_add(int type, t_simple *simple, char *data)
{
	if (type == GREAT || type == GREATGREAT)
	{
		simple_add_outfile(simple, data, type == GREATGREAT);
		return ;
	}
	simple_add_infile(simple, data, type == LESSLESS);
}

int	parse_redirect(t_cmd *cmd, t_token **tokens)
{
	int		type;
	int		start_type;

	start_type = (*tokens)->type;
	*tokens = (*tokens)->next;
	while (1)
	{
		if ((*tokens) == NULL)
			return (1);
		type = (*tokens)->type;
		if (type == WSPACE)
			*tokens = (*tokens)->next;
		else if (type & (QUOT + DQUOT + WORD + DOLL + DOLLQ))
		{
			simple_add(start_type, simple_tail(cmd->simples), (*tokens)->data);
			return (0);
		}
		else
			break ;
		continue ;
	}
	printf("Parse error: unexpected token [");
	print_token_type(type);
	printf("]\n");
	return (1);
}

int	parse_heredoc(t_cmd *cmd, t_token *token)
{
	simple_add_infile(simple_tail(cmd->simples), token->data, 1);
	return (0);
}

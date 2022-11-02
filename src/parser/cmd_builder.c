/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_builder.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:29:12 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 15:00:17 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	cmd_add_pipe(t_cmd *cmd, t_token *token)
{
	t_simple	*new;

	if (simple_tail(cmd->simples)->argv == NULL || token->next == NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("syntax error near unexpected token '|'\n", STDERR_FILENO);
		return (2);
	}
	new = new_simple(0, NULL);
	if (new == NULL)
		return (10);
	simple_add_back(&cmd->simples, new);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:34:30 by ageels        #+#    #+#                 */
/*   Updated: 2022/11/02 15:18:46 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	minishell(t_cmd *cmd, char **input)
{
	char	*retstr;

	retstr = NULL;
	if (*input == NULL)
		*input = prompt(cmd);
	if (!ft_strlen(*input) || tokenize(cmd, *input) == -1 \
	|| !cmd->tokens || heredoc(cmd, &retstr))
		return (1);
	if (retstr != NULL)
	{
		reset(cmd, *input);
		*input = retstr;
		g_errno = 0;
		return (2);
	}
	cmd->err = parse(cmd);
	if (cmd->err == 255)
		cmd->err = 0;
	else if (cmd->err == 0)
		cmd->err = execute(cmd);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;
	char	*input;
	int		to_exit;
	int		res;

	input = NULL;
	to_exit = check_c_mode(argc, argv, &input);
	res = setup(&cmd, envp);
	if (res != 0)
		return (res);
	while (1)
	{
		if (to_exit != 2 && minishell(&cmd, &input) == 1)
		{
			reset(&cmd, input);
			input = NULL;
		}
		if (to_exit != 0)
			break ;
	}
	clear_cmd(&cmd);
	return (cmd.err);
}

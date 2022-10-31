/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 22:16:11 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/31 23:40:58 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	catch_errno(t_cmd cmd)
{
	if (cmd.err == 130)
		ft_putstr_fd("^C\n", STDERR_FILENO);
	else if (cmd.err == 131)
		ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

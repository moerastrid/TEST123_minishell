/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 16:54:53 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/26 18:13:46 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	if (prompt() != 0)
	{
		ft_putstr_fd("no prompt today", 1);
		return (1);
	}
	//execute();
	//free_structs();
	t_cmd	cmds;
	cmds.amount_cmd = 4;
	//family_life(cmds);
}

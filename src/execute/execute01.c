/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute01.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:18:38 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/03 22:58:54 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// IN EXECUTE01, YOU CAN FIND THE CHILD PROCESSES AND THE PARENT :)

int	family_life(t_cmd cmds)
{
	int			pfd[2][2]; //not allowed;
	int			i;
	t_children	*new;
	pid_t		id;

	i = 0;
	while (i < cmds.cmd_count)
	{
		if (i + 1 != cmds.cmd_count)
			pipe(pfd[i % 2]);
		id = child(cmds, pfd[i % 2], pfd[(i + 1) % 2], i);
		if (id == -1)
			exit(-1); // ?
		new = new_child(id);
		if (g_children == NULL)
			g_children = new;
		else
			child_add_back(g_children, new);
		i++;
	}
	return (parent(cmds, pfd[(i + 1) % 2]));
}

int	parent(t_cmd cmds, int *pfd)
{
	int			status;
	int			exit_code;
	t_children	*child;

	child = g_children;
	exit_code = 0;
	status = 0;
	while (child)
	{
		waitpid(child->id, &status, 0);
		child = child->next;
	}
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = WTERMSIG(status) + 128;
	return (exit_code);
}

void	child_redirect(t_cmd cmds, int *write_pipe, int *read_pipe, int cmd_no)
{
	if (cmd_no != 0)
	{
		if (dup2(read_pipe[READ], STDIN_FILENO) == -1)
			exit (-1);
	}
	if (cmd_no != cmds.cmd_count - 1)
	{
		if (dup2(write_pipe[WRITE], STDOUT_FILENO) == -1)
			exit (-1);
	}
}	// system("lsof -c minishell");

static t_simple	*get_simple(t_cmd cmd, int num)
{
	int			i;
	t_simple	*simple;

	simple = cmd.simples;
	i = 0;
	while (i < num)
	{
		simple = simple->next;
		i++;
	}
	return (simple);
}

void redirect_infile(t_str_list *infiles);
void redirect_outfile(t_str_list *outfiles);

pid_t	child(t_cmd cmds, int *write_pipe, int *read_pipe, int cmd_no)
{
	pid_t		child_id;
	t_simple	*simple;

	child_id = fork();
	if (child_id == -1)
		return (-1);
	else if (child_id != 0) //parent
	{
		// close(read_pipe[WRITE]);
		if (cmd_no != 0)
			close(read_pipe[READ]);
		// if (cmd_no != cmds.cmd_count)
		close(write_pipe[WRITE]);
		return (child_id);
	}
	if (cmd_no == 0)
		redirect_infile(cmds.infiles);
	if (cmd_no == cmds.cmd_count - 1)
		redirect_outfile(cmds.outfiles);
	close(write_pipe[READ]);
	child_redirect(cmds, write_pipe, read_pipe, cmd_no);
	simple = get_simple(cmds, cmd_no);
	exec_cmd(*simple);
	return (-1);
}
//											Parent
// Pipes		[[write, read],[write, read]]			[[write, read],[write, read]]
// cmd1							| 				cmd2				| cmd3
// c1 							| 				c2 					| c3
// Reads from stdin				| 				reads from pipe		| reads from pipe
// Writes to pipe				| 				Writes to pipe		| Writes to stdout

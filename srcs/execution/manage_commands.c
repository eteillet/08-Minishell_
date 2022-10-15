/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:16:19 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/04 22:30:01 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_pid(t_global *global, int i)
{
	int	j;

	j = 0;
	while (j < global->piping_index)
	{
		global->parser[i + j].pid = 0;
		j++;
	}
}

/*
** count the nb of pipes in the pipe sequence
** store the input / output fd in infile / outfile
** redirect the fdin :
**		- if infile : infile
**		- otherwise : stdin saved in savein
*/

static int	count_pipes_and_init_redir(int i, t_global *global)
{
	global->infile = 0;
	global->outfile = 0;
	if (global->parser[i + global->piping_index].input.name)
		global->infile = global->parser[i + global->piping_index].input.fd;
	while (global->parser[i + global->piping_index].pipe)
		global->piping_index++;
	if (global->parser[i + global->piping_index].output.name)
		global->outfile = global->parser[i + global->piping_index].output.fd;
	global->piping_index++;
	save_initial_fd(global);
	if (global->infile)
		global->fdin = global->infile;
	else
	{
		global->fdin = dup(global->savein);
		if (global->fdin < 0)
			return (1);
	}
	init_pid(global, i);
	return (0);
}

static int	restore_and_wait(t_global *global, int ret_pid, int i)
{
	int		status;
	int		j;

	j = 0;
	restore_initial_fd(global);
	if (ret_pid > 0)
	{
		while (j < global->piping_index)
		{
			if (global->parser[i + j].pid > 0)
			{
				waitpid(global->parser[i + j].pid, &status, 0);
				if (WIFEXITED(status) && (j == global->piping_index - 1)
					&& errno != 130 && errno != 131)
				{
					errno = WEXITSTATUS(status);
					global->exit_code = errno;
				}
			}
			j++;
		}
	}
	return (1);
}

/*
** count nb of pipes and init input and output files
** for each pipe, we redirect input and output
** at the end, we wait parent processes
*/

static int	pipe_and_run(int i, t_global *global)
{
	int		j;
	int		ret;
	int		ret_pid;

	j = -1;
	ret_pid = 0;
	if (count_pipes_and_init_redir(i, global))
		return (1);
	while (++j < global->piping_index)
	{
		if (redir_pipe_sequence(global, i, j))
		{
			global->skip_piped_cmd += 1;
			return (restore_and_wait(global, 0, i));
		}
		ret = dispatch_cmd(global, global->parser[i + j],
				global->parser[i + j].args_for_execve, i + j);
		global->skip_piped_cmd += 1;
		if (ret > 0)
		{
			ret_pid = ret;
			ret = 0;
		}
	}
	return (restore_and_wait(global, ret_pid, i));
}

/*
** we reactivate the new behavior of the terminal (new_termios)
** after the execution
*/

void	manage_commands(t_global *global, int nb_cmd)
{
	int		i;
	int		ret;

	i = 0;
	while (i <= nb_cmd)
	{
		if (global->parser[i].exec)
		{
			global->piping_index = 0;
			global->skip_piped_cmd = 0;
			ret = pipe_and_run(i, global);
			tcsetattr(0, 0, &(global->tcaps->new_termios));
			if (ret)
				i += global->skip_piped_cmd;
		}
		else
			i++;
		if (errno == 130 || errno == 131)
			global->exit_code = errno;
	}
}

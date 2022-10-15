/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 21:35:15 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/04 22:30:38 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** we determine the output fd :
** 		- output file if there is one
** 		- otherwise the initial STDOUT saved in saveout
*/

static int	output_pipe(t_global *global)
{
	if (global->outfile)
		global->fdout = global->outfile;
	else
	{
		global->fdout = dup(global->saveout);
		if (global->fdout < 0)
			return (1);
	}
	return (0);
}

static int	redir_in(t_global *global, int i, int j)
{
	if (redirect_fd(global->fdin, STDIN_FILENO))
		return (1);
	if (global->parser[i + j].input.name && (j > 0))
	{
		global->fdin = global->parser[i + j].input.fd;
		if (redirect_fd(global->fdin, STDIN_FILENO))
			return (1);
	}
	return (0);
}

static int	redir_out(t_global *global, int i, int j)
{
	if (redirect_fd(global->fdout, STDOUT_FILENO))
		return (1);
	if (global->parser[i + j].output.name && (j != global->piping_index - 1))
	{
		global->fdout = global->parser[i + j].output.fd;
		if (redirect_fd(global->fdout, STDOUT_FILENO))
			return (1);
	}
	return (0);
}

static int	create_pipe(t_global *global)
{
	int	fdpipe[2];

	if (pipe(fdpipe) < 0)
		return (1);
	global->fdout = fdpipe[1];
	global->fdin = fdpipe[0];
	return (0);
}

/*
** we manage the input and output files and also the pipes
** if we are at the end of a pipe sequence we redirect the output
*/

int	redir_pipe_sequence(t_global *global, int i, int j)
{
	if (redir_in(global, i, j))
		return (1);
	if (j == global->piping_index - 1)
	{
		if (output_pipe(global))
			return (1);
	}
	else
	{
		if (create_pipe(global))
			return (1);
	}
	if (redir_out(global, i, j))
		return (1);
	return (0);
}

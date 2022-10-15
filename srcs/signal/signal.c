/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:20:49 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/05 16:37:10 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sig_child(int sig)
{
	static int	pid;

	if (pid)
	{
		kill(pid, sig);
		pid = 0;
	}
	else
	{
		pid = sig;
	}
	if (sig == SIGQUIT)
	{
		errno = 131;
		ft_putstr_fd("Quitter (core dumped)\n", 1);
	}
	else if (sig == SIGINT)
	{
		errno = 130;
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

/*
** we catch ctrl-C and ctrl-\ inputs in an infinite command like "cat"
*/

void	treat_child_signal(int pid)
{
	sig_child(pid);
	signal(SIGINT, sig_child);
	signal(SIGQUIT, sig_child);
}

/*
** we catch ctrl-C and ctrl-\ inputs in a normal case
** if ctrl-C we end the line after "^C" (SIGINT)
** SIGINT is handled (ctrl-C = interrupt the running process in the terminal)
** SIGQUIT is ignored in bash (ctrl-\) excep in an infinite command like "cat"
*/

static void	set_signal(int signal)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (signal == SIGINT)
	{
		ft_putstr_fd("^C\n", STDOUT_FILENO);
		errno = 130;
		g_signal = true;
		ft_putstr_fd(""YEL"[42-eteillet]"GRN"~", STDOUT_FILENO);
		ft_putstr_fd(path, STDOUT_FILENO);
		ft_putstr_fd("\n\033[0m$  ", STDOUT_FILENO);
	}
	free(path);
}

void	treat_signal(void)
{
	signal(SIGINT, set_signal);
	signal(SIGQUIT, set_signal);
}

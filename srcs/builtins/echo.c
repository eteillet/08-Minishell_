/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:54:18 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/19 16:55:15 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_newline(char *arg, int *new_line)
{
	int	i;

	i = 0;
	if (arg[0] != '-' || (arg[0] == '-' && !arg[1]))
		return (0);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	*new_line = 42;
	return (1);
}

/*
** builtin echo with option '-n'
*/

int	builtin_echo(char **arg)
{
	int		i;
	int		new_line;

	i = 1;
	new_line = 0;
	while (arg[i] && is_newline(arg[i], &new_line))
		i++;
	while (arg[i])
	{
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (arg[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 21:22:58 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/04 21:23:31 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_initial_fd(t_global *global)
{
	global->savein = dup(STDIN_FILENO);
	global->saveout = dup(STDOUT_FILENO);
}

int	redirect_fd(int old, int new)
{
	if (dup2(old, new) < 0)
		return (1);
	close(old);
	return (0);
}

int	restore_initial_fd(t_global *global)
{
	if (redirect_fd(global->savein, 0))
		return (1);
	if (redirect_fd(global->saveout, 1))
		return (1);
	return (0);
}

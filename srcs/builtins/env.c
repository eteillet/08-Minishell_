/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:59:49 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/19 17:02:27 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** builtin env without options
*/

int	builtin_env(t_global *global, char **arg)
{
	if (arg[1])
	{
		ft_putstr_fd("env : \"", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putendl_fd("\": Aucun fichier ou dossier de ce type", 2);
		return (127);
	}
	else
		print_env(global->env, false);
	return (0);
}

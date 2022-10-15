/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:51:10 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/19 17:53:08 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** builtin unset without option
*/

int	builtin_unset(t_global *global, char **arg)
{
	int		i;
	int		ret;
	int		unset;

	i = 1;
	ret = 0;
	while (arg[i])
	{
		unset = unset_env(global, arg[i]);
		if (unset == -1)
		{
			ft_putstr_fd("bash: unset: \" ", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putendl_fd(" \" : identifiant non valable", 2);
			ret = 1;
		}
		i++;
	}
	return (ret);
}

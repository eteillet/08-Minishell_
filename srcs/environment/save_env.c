/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:32:34 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 13:33:03 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** save the environment arg (envp) of main
*/

void	save_env(t_global *global, char **env)
{
	int		i;
	int		len;

	i = 0;
	len = len_env(env);
	global->env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!global->env)
		return ;
	global->env[len] = NULL;
	while (env[i])
	{
		global->env[i] = ft_strdup(env[i]);
		if (!global->env[i])
			return ;
		i++;
	}
}

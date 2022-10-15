/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_index.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:45:34 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 11:49:32 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** if the key is equal to the strlen(key) chars of env
** and
** the next char is '=' (couple key=value)
** or
** the next char doesn't exists (key alone)
*/

int	find_env_index(char *name, char **env)
{
	int	index;

	index = 0;
	if (!name || !env)
		return (-1);
	while (env[index])
	{
		if (ft_strncmp(env[index], name, ft_strlen(name)) == 0
			&& ((env[index][ft_strlen(name)]
				&& env[index][ft_strlen(name)] == '=')
					|| !env[index][ft_strlen(name)]))
			return (index);
		index++;
	}
	return (-1);
}

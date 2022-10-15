/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:47:21 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/04 22:47:00 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	correct_bashname(char *name)
{
	int	i;

	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*
** can remove an entry completely from the environment
** if the env contains the entry, the whole entry is removed
**
** return 0 if successful
** return -1 if name is null pointer, empty string or string containing an '='
*/

int	unset_env(t_global *glob, char *name)
{
	int		len;
	int		index;

	if (!name || !ft_strcmp(name, "") || ft_strchr(name, '=')
		|| !correct_bashname(name))
		return (-1);
	index = find_env_index(name, glob->env);
	if (index != -1)
	{
		len = len_env(glob->env);
		glob->env = resize_env_del(glob->env, len, index);
	}
	len = len_env(glob->env);
	if (!glob->env)
		return (-1);
	return (0);
}

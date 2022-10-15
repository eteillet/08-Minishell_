/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:30:07 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 13:32:21 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** duplicate and resize the environment and free the old one
*/

char	**resize_env_del(char **env, int size, int index_to_del)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = ft_calloc(size, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (i != index_to_del)
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env[j])
				return (NULL);
			j++;
		}
		i++;
	}
	free_env(env);
	return (new_env);
}

char	**resize_env_add(char **env, int size, char *new)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (NULL);
		i++;
	}
	new_env[i] = ft_strdup(new);
	if (!new_env[i])
		return (NULL);
	free_env(env);
	return (new_env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:49:45 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 11:50:13 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** name is the key of the couple KEY=VALUE
** we return the value corresponding to the name
*/

char	*get_env(char *name, char **env)
{
	int		index;
	char	*value;
	size_t	len_key;

	value = NULL;
	index = find_env_index(name, env);
	if (index == -1)
		return (NULL);
	len_key = ft_strlen(name);
	if (ft_strlen(env[index]) != len_key)
		value = env[index] + len_key + 1;
	return (value);
}

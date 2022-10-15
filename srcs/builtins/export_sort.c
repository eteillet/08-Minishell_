/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:43:51 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/19 17:47:37 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_key(char *line, int size)
{
	int		i;
	char	*key;

	i = 0;
	key = ft_calloc((size + 1), sizeof(char));
	if (!key)
		return (NULL);
	while (i < size)
	{
		key[i] = line[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*get_value(char *line)
{
	int		i;
	int		key_len;
	int		value_len;
	char	*value;

	i = 0;
	key_len = get_key_len(line);
	value_len = ft_strlen(line) - key_len - 1;
	if (value_len == 0)
		return (NULL);
	value = ft_calloc((value_len + 1), sizeof(char));
	if (!value)
		return (NULL);
	key_len++;
	while (line[key_len])
	{
		value[i] = line[key_len];
		key_len++;
		i++;
	}
	value[i] = '\0';
	return (value);
}

void	sort_env(char **sort_env)
{
	int		i;
	int		j;
	int		swap;
	char	*tmp;

	swap = 1;
	while (swap)
	{
		swap = 0;
		i = -1;
		while (sort_env[++i + 1])
		{
			j = 0;
			while (sort_env[i][j] && (sort_env[i][j] == sort_env[i + 1][j]))
				j++;
			if (sort_env[i][j] > sort_env[i + 1][j])
			{
				tmp = sort_env[i];
				sort_env[i] = sort_env[i + 1];
				sort_env[i + 1] = tmp;
				swap = 1;
			}
		}
	}
	print_env(sort_env, true);
}

/*
** we make a copy of the environment
*/

void	print_sorted_env(char **env)
{
	char	**cpy_env;
	int		size;

	size = len_env(env);
	cpy_env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!cpy_env)
		return ;
	cpy_env[size] = NULL;
	while (size--)
		cpy_env[size] = env[size];
	sort_env(cpy_env);
	free(cpy_env);
}

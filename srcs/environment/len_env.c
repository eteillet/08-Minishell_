/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:51:06 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 11:51:42 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	len_env_line(int i, char **env)
{
	int	j;

	j = 0;
	while (env[i][j])
		j++;
	return (j);
}

int	get_key_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	return (i);
}

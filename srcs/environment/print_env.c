/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:52:00 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 11:53:54 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_export_value(char *value, int fd)
{
	int		i;

	i = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '\\')
			ft_putchar_fd('\\', fd);
		ft_putchar_fd(value[i], fd);
		i++;
	}
}

void	print_export(char *key, char **env, char *env_line)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(key, STDOUT_FILENO);
	if (env_line[ft_strlen(key)] == '=')
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		print_export_value(get_env(key, env), STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

/*
** functions to print the environment :
** if bool export, we display in ascii order only if there is an =
** else we display in initial order (command env)
*/

void	print_env(char **env, bool export)
{
	int		i;
	int		key_size;
	char	*key;

	i = 0;
	key_size = 0;
	key = NULL;
	while (env[i])
	{
		key_size = get_key_len(env[i]);
		key = get_key(env[i], key_size);
		if (export)
		{
			print_export(key, env, env[i]);
		}
		else
		{
			if (env[i][ft_strlen(key)] && env[i][ft_strlen(key)] == '=')
				ft_putendl_fd(env[i], STDOUT_FILENO);
		}
		ft_strdel(&key);
		i++;
	}
}

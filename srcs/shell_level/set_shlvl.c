/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:26:54 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/05 16:36:25 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	get_default_path(t_global *global)
{
	char	*get_path;
	char	buffer[4096];
	int		fd;
	int		i;

	fd = open("/etc/environment", O_RDONLY);
	if (fd < 0)
		return ;
	get_path = ft_calloc(1, sizeof(char));
	i = 0;
	while (read(fd, &(buffer[i]), 1) != 0)
	{
		if (i > 5 && buffer[i] != DB_QUOTE && buffer[i] != NEWLINE)
			get_path = add_c_to_str(get_path, buffer[i]);
		i++;
	}
	set_env(global, "PATH", get_path, 0);
	ft_strdel(&get_path);
	close(fd);
}

static void	set_default_env(t_global *global)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (get_env("PWD", global->env) == NULL && dir)
		set_env(global, "PWD", dir, 0);
	if (get_env("OLDPWD", global->env) == NULL && dir)
		set_env(global, "OLDPWD", dir, 0);
	if (get_env("PATH", global->env) == NULL && dir)
		get_default_path(global);
	if (get_env("TERM", global->env) == NULL)
		put_env(global, "TERM=xterm-256color");
	ft_strdel(&dir);
}

/*
** we set the SHLVL variable when starting the program
** if it exists we increment, otherwise we create it
*/

void	set_shlvl_and_default_env(t_global *global)
{
	int		shlvl_value;
	char	*value;

	if (get_env("SHLVL", global->env) == NULL)
		put_env(global, "SHLVL=1");
	else
	{
		shlvl_value = ft_atoi(get_env("SHLVL", global->env));
		shlvl_value++;
		value = ft_itoa(shlvl_value);
		set_env(global, "SHLVL", value, 1);
		ft_strdel(&value);
	}
	set_default_env(global);
}

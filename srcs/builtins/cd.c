/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:51:12 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/04 22:31:40 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	prompt_error(int option, char *path, int ret)
{
	if (option == 0)
	{
		ft_putendl_fd("bash: cd: trop d'arguments", 2);
	}
	else if (option == 1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putendl_fd("Aucun fichier ou dossier de ce type", 2);
	}
	else if (option == 2)
	{
		ft_putstr_fd("cd : erreur de determination du repertoire actuel : ", 2);
		ft_putstr_fd("getcwd : ne peut acceder aux repertoires parents : ", 2);
		ft_putendl_fd("Aucun fichier ou dossier de ce type", 2);
		ft_putendl_fd(path, 2);
	}
	return (ret);
}

/*
** cd in a pipe sequence is an exception :
** 		- we don't change the directory
** 		- we return same error messages that a normal cd command
*/

int	builtin_cd_in_pipe(t_global *global, char **arg)
{
	char	*initial_home;
	char	*home;

	if (!arg[1] || !ft_strcmp(arg[1], "--")
		|| !ft_strcmp(arg[1], "~")
		|| !ft_strcmp(arg[1], "~/"))
		home = get_env("HOME", global->env);
	else if (!ft_strcmp(arg[1], "-"))
		home = get_env("OLDPWD", global->env);
	else
		home = arg[1];
	initial_home = getcwd(NULL, 0);
	if (chdir(home) == -1)
	{
		ft_strdel(&initial_home);
		return (prompt_error(1, NULL, 1));
	}
	else
		chdir(initial_home);
	ft_strdel(&initial_home);
	return (0);
}

/*
** builtin cd only with absolute and relative path
*/

int	builtin_cd(t_global *global, char **arg)
{
	char	*home;

	if (arg[1] && arg[2])
		return (prompt_error(0, NULL, 1));
	if (global->piping_index > 1)
		return (builtin_cd_in_pipe(global, arg));
	if (!arg[1] || !ft_strcmp(arg[1], "--")
		|| !ft_strcmp(arg[1], "~")
		|| !ft_strcmp(arg[1], "~/"))
		home = get_env("HOME", global->env);
	else if (!ft_strcmp(arg[1], "-"))
		home = get_env("OLDPWD", global->env);
	else
		home = arg[1];
	if (chdir(home) == -1)
		return (prompt_error(1, NULL, 1));
	home = getcwd(NULL, 0);
	if (!home)
		return (prompt_error(2, get_env("PWD", global->env), 0));
	set_env(global, "OLDPWD", get_env("PWD", global->env), 1);
	set_env(global, "PWD", home, 1);
	ft_strdel(&home);
	return (0);
}

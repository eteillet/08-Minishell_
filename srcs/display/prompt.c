/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:40:03 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 11:40:23 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** display the prompt
** we get the current path thanks to :
**      - the variable "PWD" if it exists (not unset)
**      - else getcwd
*/

void	prompt(char **env)
{
	char	*path;

	path = NULL;
	ft_putstr_fd(""YEL"[42-eteillet]"GRN"~", STDOUT_FILENO);
	if (get_env("PWD", env))
		ft_putstr_fd(get_env("PWD", env), STDOUT_FILENO);
	else
	{
		path = getcwd(NULL, 0);
		ft_putstr_fd(path, STDOUT_FILENO);
		ft_strdel(&path);
	}
	ft_putstr_fd("\n\033[97m$  ", STDOUT_FILENO);
}

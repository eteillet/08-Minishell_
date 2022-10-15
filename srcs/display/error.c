/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:39:24 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/04 22:44:57 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** first block if to fix norm problems
*/

void	stop_exec_and_prompt_error(t_global *glob,
		char *msg, char *tok, int ret)
{
	if (ft_strcmp(msg, "bash") == 0)
		msg = "bash : erreur de syntaxe pres du symbole inattendu << ";
	else if (ft_strcmp(msg, "semicolon_2") == 0)
		msg = "bash: erreur de syntaxe pres du symbole inattendu \" ;; \"";
	else if (ft_strcmp(msg, "semicolon_1") == 0)
		msg = "bash: erreur de syntaxe pres du symbole inattendu \" ; \"";
	if (tok)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(tok, 2);
		ft_putendl_fd(" >>", 2);
	}
	else
		ft_putendl_fd(msg, 2);
	if (ret != -1)
		glob->exit_code = ret;
	glob->fatal_error = true;
}

int	error_command(t_global *glob, char *cmd, int exit, int ret)
{
	glob->exit_code = exit;
	errno = ENOENT;
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(" : commande introuvable", 2);
	return (ret);
}

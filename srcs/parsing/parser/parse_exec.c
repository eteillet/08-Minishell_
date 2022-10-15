/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:11:35 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/05 16:11:37 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
** store the exec in the parser structure
*/

void	parse_executable(t_global *glob, int i, t_token *tok)
{
	if (tok->type == TOK_EXEC || tok->type == TOK_BUILTIN)
		glob->parser[i].exec = ft_strdup(tok->value);
	else
		return ;
}

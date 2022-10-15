/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 09:25:38 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/23 09:26:50 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	assign_type_operator(t_lexer *lex, t_token *tok)
{
	if (!ft_strcmp(tok->value, ">>"))
		tok->type = TOK_APPEND;
	if (!ft_strcmp(tok->value, ">"))
		tok->type = TOK_OUTPUT;
	if (!ft_strcmp(tok->value, "<"))
		tok->type = TOK_INPUT;
	if (!ft_strcmp(tok->value, "|"))
	{
		tok->type = TOK_PIPE;
		lex->cmd_found = false;
	}
}

int	is_operator(char *str, int i)
{
	if ((str[i] == PIPE || str[i] == SEMICOLON)
		&& not_quoted_not_escaped(str, i))
		return (1);
	if ((str[i] == INPUT || str[i] == OUTPUT)
		&& not_quoted_not_escaped(str, i))
		return (2);
	return (0);
}

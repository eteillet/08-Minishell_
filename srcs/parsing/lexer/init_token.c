/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 09:24:06 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/15 11:55:59 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	init_token(t_lexer *lex)
{
	int	i;

	i = 0;
	lex->token[lex->index] = malloc_token();
	lex->token[lex->index]->value = ft_calloc(1, sizeof(char));
	lex->token[lex->index]->start = false;
	lex->token[lex->index]->type = TOK_TXT;
	lex->token[lex->index]->end = false;
	lex->token[lex->index]->ind_exp = 0;
	lex->token[lex->index]->error_expand = false;
	while (i < SIZE_EXPAND_TAB)
	{
		lex->token[lex->index]->index_to_expand[i] = -1;
		i++;
	}
}

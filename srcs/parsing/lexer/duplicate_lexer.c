/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:32:22 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 18:32:47 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
** if the maximum nb of tokens is reached,
** create a token** twice as large
** in which we copy our tokens before free them
*/

void	copy_token(t_token *src, t_token *dest)
{
	dest->value = ft_strdup(src->value);
	dest->start = src->start;
	dest->type = src->type;
}

t_token	**initial_lexer_is_not_enough(t_lexer *lex)
{
	int			i;
	t_token		**bigger;

	i = 0;
	lex->token_capacity *= 2;
	bigger = ft_calloc((lex->token_capacity + 1), sizeof(t_token *));
	if (!bigger)
		return (NULL);
	if (lex)
	{
		while (lex->token[i] && i <= lex->index)
		{
			bigger[i] = malloc_token();
			copy_token(lex->token[i], bigger[i]);
			i++;
		}
		free_token(lex->token);
	}
	return (bigger);
}

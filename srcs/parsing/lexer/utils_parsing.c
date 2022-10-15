/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:33:40 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/23 14:42:31 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	only_space_before(t_lexer *lex, char *input)
{
	int	i;

	i = 0;
	while (input[i] && i < lex->pos)
	{
		if (!is_space(input[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
** we search the first token of a command
** it will be the entry point for the parser
** first if :
**		- pos = 0 or only spaces before
**		- previous token is a pipe
**		- if tok - 2 is : > < or >> :
**				. only if not already a cmd found
*/

int	is_first_token(t_lexer *lex, int index, char *input)
{
	int	ret;

	ret = 0;
	if (lex->token[index])
	{
		if (((lex->pos == 0 || only_space_before(lex, input))
				&& !is_operator(lex->token[index]->value, 0))
			|| (index > 0 && lex->token[index - 1]->type == TOK_PIPE))
		{
			lex->token[index]->start = true;
			ret = 1;
		}
		if (index > 1 && (lex->token[index - 2]->type == TOK_INPUT
				|| lex->token[index - 2]->type == TOK_OUTPUT
				|| lex->token[index - 2]->type == TOK_APPEND)
			&& lex->cmd_found == false)
		{
			lex->token[index]->start = true;
			ret = 1;
		}
	}
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ope_and_comment_tok.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:59:25 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/05 14:59:28 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
** skip the end of the line to not display it
*/

int	create_comment_tok(char *s, int i)
{
	int	len;

	len = ft_strlen(s) - i;
	return (len);
}

int	create_operator_tok(t_lexer *lex, t_token *tok, char *s, int i)
{
	int	size;

	size = 1;
	tok->value = add_c_to_str(tok->value, s[i]);
	if (s[i] == OUTPUT && s[i + 1] && s[i + 1] == OUTPUT)
	{
		i++;
		size = 2;
		tok->value = add_c_to_str(tok->value, s[i]);
	}
	assign_type_operator(lex, tok);
	return (size);
}

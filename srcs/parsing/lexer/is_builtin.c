/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 09:24:56 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/05 09:16:32 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_builtin(char *tok)
{
	if (!ft_strcmp(tok, "echo") || !ft_strcmp(tok, "cd")
		|| !ft_strcmp(tok, "pwd") || !ft_strcmp(tok, "export")
		|| !ft_strcmp(tok, "unset") || !ft_strcmp(tok, "env")
		|| !ft_strcmp(tok, "exit"))
		return (1);
	return (0);
}

/*
**  we check if the exec is a builtin
*/

void	is_builtin_else_exec(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer->token[i])
	{
		if (lexer->token[i]->start == true)
		{
			if (is_builtin(lexer->token[i]->value))
				lexer->token[i]->type = TOK_BUILTIN;
			else
				lexer->token[i]->type = TOK_EXEC;
		}
		i++;
	}
}

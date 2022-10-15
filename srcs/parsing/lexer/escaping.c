/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escaping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:39:54 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 18:42:17 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	skip_backslash_begin(t_token *tok, char *line, int *i)
{
	int	tmp;

	tmp = *i;
	while (line[*i] == BACKSLASH)
	{
		if (!is_escaped(line, *i))
			*i += 1;
		if (is_escaped(line, *i))
		{
			tok->value = add_c_to_str(tok->value, line[*i]);
			*i += 1;
		}
	}
	return (*i - tmp);
}

/*
** count the number of backslash before the current char
*/

int	is_escaped(char *str, int i)
{
	int	count;

	count = 0;
	if (i > 0)
	{
		i--;
		while (i && str[i] == BACKSLASH)
		{
			count++;
			i--;
		}
	}
	return (count % 2);
}

/*
** if we have an odd nb of quotes before, it means that we are between quotes
*/

static int	is_quoted(char *line, int index)
{
	int		i;
	int		single_quote;
	int		double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (i < index)
	{
		if (line[i] == '\'' && !is_escaped(line, i))
			single_quote++;
		if (line[i] == '\"' && !is_escaped(line, i))
			double_quote++;
		i++;
	}
	if (single_quote % 2 != 0 || double_quote % 2 != 0)
		return (1);
	return (0);
}

/*
** we check that the char is not quoted or escaped
*/

int	not_quoted_not_escaped(char *line, int index)
{
	if (is_quoted(line, index))
		return (0);
	if (is_escaped(line, index))
		return (0);
	return (1);
}

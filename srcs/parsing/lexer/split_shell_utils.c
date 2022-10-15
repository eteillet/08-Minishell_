/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:14:45 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/23 12:18:18 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	nothing_before(char *str, int index, char c)
{
	if (index > 0)
	{
		index--;
		while (index && (str[index] != c
				|| (str[index] == c && is_escaped(str, index))))
		{
			if (str[index] != ' ' && str[index] != '\t')
				return (0);
			index--;
		}
	}
	return (1);
}

int	nothing_after(char *str, int index)
{
	if (str[index + 1])
	{
		index++;
		while (str[index])
		{
			if (str[index] != ' ' && str[index] != '\t' && str[index] != '\0')
				return (0);
			index++;
		}
	}
	return (1);
}

static void	prompt_semicolon_error(t_global *global, char *type_msg)
{
	stop_exec_and_prompt_error(global, type_msg, NULL, 2);
	return ;
}

/*
** error if :
**		- 2 ;; without anything between them
**		- begin by ; or 2 ;; side by side
*/

void	check_valid_semicolons(t_global *global, char *str)
{
	size_t	i;
	char	*trim;

	i = 0;
	trim = ft_strtrim(str, " \t");
	if (ft_strlen(trim) == 1 && trim[0] == SEMICOLON)
	{
		ft_strdel(&trim);
		return (prompt_semicolon_error(global, "semicolon_1"));
	}
	ft_strdel(&trim);
	while (str[i])
	{
		if (str[i] == SEMICOLON && not_quoted_not_escaped(str, i)
			&& str[i + 1] && str[i + 1] == SEMICOLON
			&& not_quoted_not_escaped(str, i + 1))
			return (prompt_semicolon_error(global, "semicolon_2"));
		if (str[i] == SEMICOLON && not_quoted_not_escaped(str, i)
			&& nothing_before(str, i, SEMICOLON) && !nothing_after(str, i))
			return (prompt_semicolon_error(global, "semicolon_1"));
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:24:09 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/23 14:26:21 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
** store the "normal" arguments in the parser structure
** if tok->value is empty, we skip the token
** replace $? by the last return
*/

void	parse_str(t_global *glob, int i, t_token *tok)
{
	char	*expand_last_ret;

	expand_last_ret = NULL;
	expand_last_ret = is_expand_last_ret(glob, tok->index_to_expand,
			tok->value, 0);
	if (expand_last_ret)
		glob->parser[i].argv
			= add_str_to_end_array(glob->parser[i].argv,
				expand_last_ret);
	else
		glob->parser[i].argv
			= add_str_to_end_array(glob->parser[i].argv, tok->value);
	ft_strdel(&expand_last_ret);
}

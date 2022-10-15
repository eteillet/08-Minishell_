/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_last_ret_expansion.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:11:42 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/05 16:11:43 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_an_expand_index(int *tab_index, int i)
{
	int	j;

	j = 0;
	while (tab_index[j] != -1)
	{
		if (i == tab_index[j])
			return (1);
		j++;
	}
	return (0);
}

static char	*itoa_and_skip(int last_ret, int *i)
{
	char	*ret;

	ret = ft_itoa(last_ret);
	*i += 2;
	return (ret);
}

static char	*join_ret(char **s, char **ret)
{
	char	*new;

	new = NULL;
	new = ft_strjoindelone(*s, *ret);
	ft_strdel(ret);
	return (new);
}

/*
** check if there is in the tok->value (s) a $? to expand
** if it's to expand :
**		- we replace $? by the last return
**		- we skip $? in tok->value
**		- we concatenate with therest of tok->value
*/

char	*is_expand_last_ret(t_global *glob, int *tab_index, char *s, int i)
{
	char	*new;
	char	*ret;

	new = ft_calloc(1, sizeof(char));
	ret = NULL;
	while (s[i])
	{
		if (s[i + 1] && ft_strncmp(&s[i], "$?", 2) == 0
			&& is_an_expand_index(tab_index, i))
			ret = itoa_and_skip(glob->last_ret, &i);
		if (ret)
			new = join_ret(&new, &ret);
		if (!s[i])
			break ;
		if (s[i + 1] && ft_strncmp(&s[i], "$?", 2) == 0
			&& is_an_expand_index(tab_index, i))
			i -= 1;
		else if (s[i] && (!s[i + 1] || (ft_strncmp(&s[i], "$?", 2) != 0
					|| !is_an_expand_index(tab_index, i))))
			new = add_c_to_str(new, s[i]);
		else
			break ;
		i++;
	}
	return (new);
}

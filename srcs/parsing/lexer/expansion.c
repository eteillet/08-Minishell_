/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:54:19 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/05 09:18:58 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	replace_key_by_value(t_token *tok, char *key, char **env)
{
	char	*value;

	value = get_env(key, env);
	if (value)
		tok->value = ft_strjoindelone(tok->value, value);
	ft_strdel(&key);
	if (!value)
		tok->error_expand = true;
}

/*
** count the nb of non escaped char c before in the string
*/

int	cnt_char_before(char *s, int i, char c)
{
	int		j;
	int		cnt;

	j = 0;
	cnt = 0;
	while (j < i)
	{
		if (s[j] == c && !is_escaped(s, i))
			cnt++;
		j++;
	}
	return (cnt);
}

/*
** store the index of the $? to expand in the future parser
*/

static void	store_index_to_expand_ret(t_token *tok)
{
	tok->index_to_expand[tok->ind_exp++] = ft_strlen(tok->value);
	tok->value = add_c_to_str(tok->value, '$');
}

/*
** expand after '$'
**		- ?					-> display last return
**		- digit				-> display nothing and skip '$'
**		- key of env var	-> corresponding value
*/

int	expand_var(t_global *global, t_token *tok, char *line, int i)
{
	int			len_key;
	char		*key;
	int			tmp_i;

	len_key = 0;
	tmp_i = ++i;
	if (line[i] == '?')
		store_index_to_expand_ret(tok);
	if (ft_isdigit(line[i]) || line[i] == '*' || (line[i] == DB_QUOTE
			&& (cnt_char_before(line, i, DB_QUOTE)) % 2 == 0))
		return (1);
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_')
		&& (!is_space(line[i])
			|| (line[i] == BACKSLASH && is_space(line[i + 1]))))
	{
		if (line[i] == BACKSLASH)
			break ;
		len_key++;
		i++;
	}
	key = get_key(&(line[tmp_i]), len_key);
	if (key)
		replace_key_by_value(tok, key, global->env);
	return (len_key);
}

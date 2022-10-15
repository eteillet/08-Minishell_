/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:19:53 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/05 14:41:14 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	count_db_quotes(char *s, int i, int *nb_quote)
{
	if (s[i] == DB_QUOTE && !is_escaped(s, i))
		*nb_quote += 1;
}

static int	process_db_quote_tok(t_global *glob, t_token *tok, char *s, int i)
{
	if (s[i] == DB_QUOTE && !is_escaped(s, i) && s[i + 1] == SG_QUOTE)
		i += create_sg_quote_tok(tok, s, i + 1);
	else if (s[i] == DB_QUOTE && !is_escaped(s, i)
		&& s[i + 1] && s[i + 1] != SPACE)
		i += 0;
	else if (s[i] == BACKSLASH && (s[i + 1] == BACKSLASH
			|| s[i + 1] == DOLLAR || (s[i + 1] == DB_QUOTE
				&& cnt_char_before(s, i + 1, DB_QUOTE) % 2 == 0)
			|| s[i + 1] == BK_QUOTE) && !is_escaped(s, i))
		i += 0;
	else if (s[i] == DOLLAR && !is_escaped(s, i) && s[i + 1]
		&& !is_space(s[i + 1]) && s[i + 1] != BACKSLASH && s[i + 1] != DB_QUOTE
		&& (ft_isalnum(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '_'
			|| s[i + 1] == '*' || s[i + 1] == '?'))
		i += expand_var(glob, tok, s, i);
	else
		tok->value = add_c_to_str(tok->value, s[i]);
	return (i);
}

/*
** return the number of char readed (with the quotes)
** we stop when we have found a non escaped db quote
** followed by a space or by a \ followed by a space
*/

int	create_db_quote_tok(t_global *glob, t_token *tok, char *s, int i)
{
	int		tmp;
	int		nb_quote;

	tmp = i++;
	nb_quote = 1;
	while (s[i] && (s[i] != DB_QUOTE || (s[i] == DB_QUOTE && is_escaped(s, i)))
		&& (nb_quote % 2) != 0)
	{
		count_db_quotes(s, i, &nb_quote);
		i = process_db_quote_tok(glob, tok, s, i);
		if (((s[i] == DB_QUOTE && !is_escaped(s, i) && !s[i + 1])
				|| (s[i + 1] && s[i + 1] == SPACE)) && (nb_quote % 2) == 0)
			break ;
		i++;
	}
	i++;
	return (i - tmp);
}

/*
** return the number of char readed (with the quotes)
*/

int	create_sg_quote_tok(t_token *tok, char *s, int i)
{
	int	tmp;

	tmp = i++;
	while (s[i] && s[i] != SG_QUOTE)
	{
		tok->value = add_c_to_str(tok->value, s[i]);
		if (!s[i + 1])
			break ;
		i++;
	}
	i++;
	if (s[i - 1] == '\0' || s[i] == '\0' || (s[i] && s[i] == SPACE))
		tok->end = true;
	return (i - tmp);
}

/*
** last if is to avoid invalid read because we skip the quotes,
** we could be out of line
*/

int	create_string_tok(t_global *glob, t_token *tok, char *s, int i)
{
	int	tmp;

	tmp = i;
	while (s[i] && !is_operator(s, i) && !is_space(s[i]) && !(tok->end))
	{
		if (s[i] == SG_QUOTE && !is_escaped(s, i))
			i += create_sg_quote_tok(tok, s, i) - 1;
		else if (s[i] == DB_QUOTE && !is_escaped(s, i))
			i += create_db_quote_tok(glob, tok, s, i) - 1;
		else if (s[i] == BACKSLASH && !is_escaped(s, i))
			i += 0;
		else if (s[i] == DOLLAR && !is_escaped(s, i)
			&& s[i + 1] && (s[i + 1] == DB_QUOTE || s[i + 1] == SG_QUOTE))
			i += 0;
		else if ((s[i] == DOLLAR && !is_escaped(s, i) && s[i + 1]
				&& !is_space(s[i + 1]) && s[i + 1] != BACKSLASH)
			&& (ft_isalnum(s[i + 1]) || s[i + 1] == '_'
				|| s[i + 1] == '*' || s[i + 1] == '?'))
			i += expand_var(glob, tok, s, i);
		else
			tok->value = add_c_to_str(tok->value, s[i]);
		if (i < (int)ft_strlen(s))
			i++;
	}
	return (i - tmp);
}

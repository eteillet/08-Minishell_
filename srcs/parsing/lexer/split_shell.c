/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:08:26 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/04 22:48:51 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_cnt_wd(char *s, char c)
{
	int		i;
	int		nb_words;

	nb_words = 0;
	if (s[0] && s[0] != c)
		nb_words++;
	i = 0;
	while (i < (int)ft_strlen(s))
	{
		if (s[i] == c && not_quoted_not_escaped(s, i))
			nb_words++;
		i++;
	}
	return (nb_words);
}

static int	ft_len_wd(char *s, char c)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	if (s[0] == c)
		i = 0;
	while (s[++i])
	{
		if (s[i])
		{
			if (i == 0 && s[i] != c)
				len++;
			else if (s[i] == c && not_quoted_not_escaped(s, i))
				break ;
			else
				len++;
		}
	}
	return (len);
}

/*
** add argument w to fix norm
*/

char	**split_shell(t_global *global, char *s, char c, int w)
{
	char	**split;
	int		j;
	int		l;
	int		len_wd;

	check_valid_semicolons(global, s);
	split = malloc(sizeof(char *) * (ft_cnt_wd((char *)s, c) + 1));
	if (!split)
		return (NULL);
	j = 0;
	while (w < ft_cnt_wd((char *)s, c))
	{
		len_wd = ft_len_wd(&s[j], c);
		split[w] = ft_calloc((len_wd + 1), sizeof(char));
		if (!split[w])
			return (NULL);
		l = 0;
		while (s[j] == c)
			j++;
		while (s[j] && l < len_wd)
			split[w][l++] = s[j++];
		w++;
	}
	split[w] = 0;
	return (split);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:41:47 by eteillet          #+#    #+#             */
/*   Updated: 2020/11/21 15:08:32 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates and returns an array of strings obtained by separating str from
** using the character c, used as a delimiter
*/

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_cnt_wd_init(char const *s, char *set, int *w, int *j)
{
	int		i;
	int		nb_words;

	if (w != NULL)
		*w = 0;
	if (j != NULL)
		*j = 0;
	nb_words = 0;
	if (s[0] && !is_in_set(s[0], set))
		nb_words++;
	i = 0;
	while (i < (int)ft_strlen(s))
	{
		if (is_in_set(s[i], set) && !is_in_set(s[i + 1], set) && s[i + 1])
			nb_words++;
		i++;
	}
	return (nb_words);
}

static int	ft_len_wd(char const *s, char *set)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (s[++i])
	{
		if ((i == 0 && !is_in_set(s[i], set))
			|| (!is_in_set(s[i], set) && s[i - 1]))
			len++;
	}
	return (len);
}

char	**ft_split_set(char *s, char *set)
{
	char	**split;
	int		w;
	int		j;
	int		l;

	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (ft_cnt_wd_init(s, set, &w, &j) + 1));
	if (!split)
		return (NULL);
	while (w < ft_cnt_wd_init(s, set, NULL, NULL))
	{
		split[w] = malloc(sizeof(char) * (ft_len_wd(&s[j], set) + 1));
		if (!split[w])
			return (NULL);
		l = 0;
		while (is_in_set(s[j], set))
			j++;
		while (!is_in_set(s[j], set) && s[j])
			split[w][l++] = s[j++];
		split[w][l] = '\0';
		w++;
	}
	split[w] = 0;
	return (split);
}

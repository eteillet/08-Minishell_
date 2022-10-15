/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:06:00 by eteillet          #+#    #+#             */
/*   Updated: 2020/11/17 11:06:03 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** strtrim removes all set characters
** from the beginning and the end of a string
*/

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*new;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len && ft_strchr(set, s1[len]))
		len--;
	new = ft_substr((char *)s1, 0, len + 1);
	return (new);
}

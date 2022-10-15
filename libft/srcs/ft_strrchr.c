/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:06:18 by eteillet          #+#    #+#             */
/*   Updated: 2020/11/17 11:06:21 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** returns a pointer to the last occurrence of the character c in the string s
*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if (s)
	{
		while (s[i] != c && i)
			i--;
		if (s[i] == c)
			return ((char *)(s + i));
	}
	return (NULL);
}

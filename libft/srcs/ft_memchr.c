/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:35:57 by eteillet          #+#    #+#             */
/*   Updated: 2020/11/17 15:36:01 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The memchr() function scans the initial n bytes of the memory area
** pointed to by s for the first instance of c.  Both c and the bytes of
** the memory area pointed to by s are interpreted as unsigned char.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_cpy;
	size_t			i;

	s_cpy = (unsigned char *)s;
	i = 0;
	while (i < n && s_cpy[i] != (unsigned char)c)
		i++;
	if (i == n)
		return (NULL);
	return ((void *)s_cpy + i);
}

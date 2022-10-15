/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:53:51 by eteillet          #+#    #+#             */
/*   Updated: 2020/11/21 14:56:00 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The memcpy() function copies n bytes from memory area src to memory
** area dest.  The memory areas must not overlap
*/

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d_cpy;
	const unsigned char	*s_cpy;

	d_cpy = (unsigned char *)dest;
	s_cpy = (unsigned char *)src;
	if (!d_cpy && !s_cpy)
		return (NULL);
	while (n--)
		*d_cpy++ = *s_cpy++;
	return (dest);
}

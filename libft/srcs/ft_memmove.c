/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:52:21 by eteillet          #+#    #+#             */
/*   Updated: 2020/11/21 14:51:21 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The memmove() function copies n bytes from memory area src
** to memory area dest.
** The memory areas may overlap: copying takes place as though the bytes in src
** are first copied into a temporary array that does not overlap src or dest,
** and the bytes are then copied from the temporary array to dest.
*/

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d_cpy;
	unsigned char	*s_cpy;

	d_cpy = (unsigned char *)dest;
	s_cpy = (unsigned char *)src;
	if ((!d_cpy && !s_cpy) || n < 1)
		return (d_cpy);
	if (dest > src)
		while (n--)
			*(d_cpy + n) = *(s_cpy + n);
	else
		while (n--)
			*(d_cpy++) = *(s_cpy++);
	return (dest);
}

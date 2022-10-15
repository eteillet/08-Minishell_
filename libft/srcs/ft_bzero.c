/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:49:55 by eteillet          #+#    #+#             */
/*   Updated: 2020/11/17 15:49:58 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** the function bzero() writes '0' into memory bytes starting
** at the byte pointed to by s and continuing through bytes s + (n - 1).
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*buffer;
	size_t			i;

	buffer = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		buffer[i] = 0;
		i++;
	}
}

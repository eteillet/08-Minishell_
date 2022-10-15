/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:34:08 by eteillet          #+#    #+#             */
/*   Updated: 2020/11/17 11:34:10 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	s_len;

	if (!dest || !src)
		return (0);
	s_len = 0;
	while (src[s_len])
		++s_len;
	if (size == 0)
		return (s_len);
	i = 0;
	while ((i + 1) < size && src[i])
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (s_len);
}

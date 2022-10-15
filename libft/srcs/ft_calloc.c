/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:48:01 by eteillet          #+#    #+#             */
/*   Updated: 2020/11/19 11:46:23 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The calloc() function allocates memory for an array of count elements
** of size bytes each and returns a pointer to the allocated memory.
** The memory is set to zero.
*/

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*new;
	size_t	total_size;
	size_t	i;

	total_size = count * size;
	new = malloc(total_size);
	if (!new)
		return (NULL);
	i = 0;
	while (total_size--)
		new[i++] = 0;
	return ((void *)new);
}

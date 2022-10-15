/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:50:02 by eteillet          #+#    #+#             */
/*   Updated: 2020/11/17 11:51:15 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** fills the first n bytes of the memory area pointed
** to by pointer with value
*/

#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t n)
{
	char	*start;

	start = pointer;
	while (n)
	{
		*start = (unsigned char)value;
		start++;
		n--;
	}
	return (pointer);
}

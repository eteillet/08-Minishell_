/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:45:18 by eteillet          #+#    #+#             */
/*   Updated: 2020/11/17 15:45:23 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** converts int data type to string data type.
*/

#include "libft.h"

static int	ft_digit_count(long int nb)
{
	int	i;

	i = 1;
	if (nb < 0)
		i++;
	while (nb)
	{
		nb /= 10;
		if (!nb)
			break ;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*new;
	int			i;
	long int	nb;

	i = ft_digit_count(n);
	new = (char *)malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	new[i] = '\0';
	nb = n;
	if (nb < 0)
		nb *= -1;
	while (i--)
	{
		new[i] = nb % 10 + '0';
		nb /= 10;
	}
	if (n < 0)
		new[0] = '-';
	return (new);
}

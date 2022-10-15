/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_last_char_in_str.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:11:14 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 18:12:03 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** lets the know if the current char c is the last char c of the string str
*/

int	is_last_char_in_str(char *str, int i, char c)
{
	if (str[i + 1])
	{
		i++;
		while (str[i])
		{
			if (str[i] == c)
				return (0);
			i++;
		}
	}
	return (1);
}

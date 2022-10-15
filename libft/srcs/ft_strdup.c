/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:38:01 by eteillet          #+#    #+#             */
/*   Updated: 2020/11/17 11:39:52 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** returns a pointer to a new string which is a duplicate of the string s.
*/

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*cpy;

	cpy = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (src[i])
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

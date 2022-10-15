/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:05:28 by eteillet          #+#    #+#             */
/*   Updated: 2020/11/17 11:05:48 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** #1. string from which to extract the new string
** #2. start index of the new string
** #3. maximum size of the new string
** Allocates and returns a string of characters
** from the string given in argument
** This new string begins at the 'start' index and has the maximum size "len"
*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	new = (char *)malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	while (s[start] && i < len)
		new[i++] = s[start++];
	new[i] = '\0';
	return (new);
}

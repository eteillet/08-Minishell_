/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoindelone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:30:01 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/21 10:31:31 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** concatenate s1 and s2 in new allocate string
** free s1 and s2
*/

char	*ft_strjoindel(char *s1, char *s2)
{
	char	*result;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = 0;
	len_s2 = 0;
	if (s1)
		len_s1 = ft_strlen(s1);
	if (s2)
		len_s2 = ft_strlen(s2);
	result = ft_strnew(len_s1 + len_s2);
	if (!result)
		return (NULL);
	if (s1)
		ft_strlcpy(result, s1, (len_s1 + 1));
	if (s2)
		ft_strlcpy(result + len_s1, s2, (len_s2 + 1));
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (result);
}

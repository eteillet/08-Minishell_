/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_c_to_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:09:42 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 18:09:59 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** add a char at the end of a char*
** return the new string and free the old one
*/

char	*add_c_to_str(char *old, char c)
{
	size_t	old_len;
	char	*new;

	old_len = ft_strlen(old);
	new = malloc(sizeof(char) * (old_len + 2));
	if (!new)
		return (NULL);
	ft_memcpy(new, old, (old_len + 2 - sizeof(char)));
	new[old_len] = c;
	new[old_len + 1] = '\0';
	free(old);
	return (new);
}

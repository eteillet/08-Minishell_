/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_str_to_beginning_array.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:10:06 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 18:10:27 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** add a char* at the beginning of a char**
** return the new array of strings and free the old one
*/

char	**add_str_to_beginning_array(char *to_add, char **array)
{
	int		array_len;
	int		i;
	int		j;
	char	**new_array;

	i = 0;
	j = 0;
	new_array = NULL;
	if (array)
	{
		array_len = split_count(array);
		new_array = (char **)malloc(sizeof(char *) * (array_len + 2));
		if (!new_array)
			return (NULL);
		new_array[i++] = to_add;
		while (array[j])
		{
			new_array[i] = array[j];
			i++;
			j++;
		}
		new_array[i] = NULL;
	}
	return (new_array);
}

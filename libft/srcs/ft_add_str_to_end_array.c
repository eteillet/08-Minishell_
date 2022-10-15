/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_str_to_end_array.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:10:34 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 18:10:50 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** add a char* at the end of a char**
** return the new array of strings and free the old one
*/

char	**add_str_to_end_array(char **array, char *to_add)
{
	int		array_len;
	int		i;
	char	**new_array;

	i = 0;
	new_array = NULL;
	if (array)
	{
		array_len = split_count(array);
		new_array = (char **)malloc(sizeof(char *) * (array_len + 2));
		if (!new_array)
			return (NULL);
		while (array[i])
		{
			new_array[i] = array[i];
			i++;
		}
		new_array[i] = ft_strdup(to_add);
		i++;
		new_array[i] = NULL;
		free(array);
	}
	return (new_array);
}

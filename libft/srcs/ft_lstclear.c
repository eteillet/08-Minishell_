/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:42:51 by eteillet          #+#    #+#             */
/*   Updated: 2020/11/21 15:45:22 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** # 1. The address of the pointer to an item
** # 2. The address of the function allowing delete the content of an item
** Deletes and frees the memory of the element passed in parameter,
** and all the following elements, to using del and free
** Finally, the initial pointer must be set to NULL.
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = temp;
		}
	}
}

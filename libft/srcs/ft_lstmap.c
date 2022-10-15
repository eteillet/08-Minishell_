/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:39:37 by eteillet          #+#    #+#             */
/*   Updated: 2020/11/21 16:01:35 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** #1. The address of the pointer to an item
** #2. The address of the function to apply
** Returns the new list. NULL if the allocation fails.
** Iterates over the list lst and applies the function f
** to the content of each item.
** Create a new list resulting from the successive applications of f
** The function del is there to destroy the contents of a element if necessary
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_element;

	new_lst = NULL;
	while (lst && f)
	{
		new_element = ft_lstnew(f(lst->content));
		if (!new_element)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_element);
		lst = lst->next;
	}
	return (new_lst);
}

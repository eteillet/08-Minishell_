/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:41:05 by eteillet          #+#    #+#             */
/*   Updated: 2020/11/21 15:47:14 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** #1 The address of the pointer to an element.
** #2. The address of the function to apply.
** Iterates over the list lst and applies the function f
** to the contained each item.
*/

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	temp = lst;
	while (temp && f)
	{
		f(temp->content);
		temp = temp->next;
	}
}

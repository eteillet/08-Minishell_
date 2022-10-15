/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:44:45 by eteillet          #+#    #+#             */
/*   Updated: 2020/11/21 15:14:18 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** # 1. The address of the pointer to the first element from the list
** # 2. The address of the pointer to the element to add to the list
** Adds the new element to the end of the list
** if the list is empty, we add *new, otherwise we look for the last
** one and we just add *new after
*/

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (!(*alst))
		*alst = new;
	else
	{
		last = ft_lstlast(*alst);
		last->next = new;
		new->next = NULL;
	}
}

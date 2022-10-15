/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:43:28 by eteillet          #+#    #+#             */
/*   Updated: 2020/11/21 15:15:53 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** # 1. The address of the pointer to the first element from the list.
** # 2. The address of the pointer to the element to add to the list.
**  Add the new element to the start of the list
*/

#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	t_list	*current;

	current = *alst;
	*alst = new;
	new->next = current;
}

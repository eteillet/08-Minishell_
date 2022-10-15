/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:41:57 by eteillet          #+#    #+#             */
/*   Updated: 2020/11/21 15:46:25 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** # 1. The free element
** # 2. The address of the function allowing delete the content of the element.
** Free the memory of the element passed in argument using
** the del function then with free
** The next memory must not be free.
*/

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del)
		del(lst->content);
	free(lst);
}

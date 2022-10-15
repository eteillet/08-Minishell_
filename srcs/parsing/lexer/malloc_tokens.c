/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 10:26:48 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/23 10:27:31 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_token	*malloc_token(void)
{
	t_token	*current;

	current = malloc(sizeof(t_token));
	if (!current)
		return (NULL);
	return (current);
}

char	*calloc_token_value(int len)
{
	char	*current_value;

	current_value = ft_calloc((len + 1), sizeof(char));
	if (!current_value)
		return (NULL);
	return (current_value);
}

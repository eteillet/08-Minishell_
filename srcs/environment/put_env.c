/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:58:57 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 11:59:25 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** adds or remove definitions from the environment
** if the function is successful it returns 0,
** otherwise non-zero value and errno is set to indicate the error
*/

int	put_env(t_global *global, char *str)
{
	int	len;

	if (!str || !ft_strchr(str, '='))
		return (-1);
	len = len_env(global->env);
	global->env = resize_env_add(global->env, len + 1, str);
	if (!*global->env)
		return (-1);
	return (0);
}

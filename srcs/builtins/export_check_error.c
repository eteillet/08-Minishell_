/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:42:26 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/04 22:42:42 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	prompt_export_error(char *key)
{
	ft_putstr_fd("bash: export: \" ", 2);
	ft_putstr_fd(key, 2);
	ft_putendl_fd(" \" : identifiant non valable", 2);
}

/*
** fisrst and last char have to be alpha or '_'
** others can be alphanum or '_'
*/

int	check_key_syntax(char *key)
{
	int		i;
	int		ret;

	ret = 1;
	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		prompt_export_error(key);
		return (0);
	}
	i = 0;
	while (key[i + 1])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			ret = 0;
		i++;
	}
	if (key[i] == '+')
		ret = 2;
	else if (key[i] && !ft_isalnum(key[i]) && key[i] != '_')
		ret = 0;
	if (ret == 0)
		prompt_export_error(key);
	return (ret);
}

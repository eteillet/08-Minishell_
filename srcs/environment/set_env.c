/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:33:24 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 13:47:08 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_strdupcat(char *s1, char sep, char *s2, int len)
{
	int		i;
	int		j;
	char	*new;

	if (!s1 || !sep || !s2 || !len)
		return (NULL);
	new = ft_calloc(len, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	new[i++] = sep;
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

/*
** add a new definition to the environment
** also true if value is an empty string but not with a null pointer
**
** name = name of the variable
** value = value of the variable
** replace =    1 -> we always replace the variable
**              0 -> we don't replace if the new variable already exists,
**				otherwise, we replace
**
** return 0 if successful
** return non-zero value otherwise and errno is set to indicate the error
**
** if index = -1, the key doesn't exists so we add it with put_env
** else the key exists and we replace the value
*/

int	set_env(t_global *global, char *name, char *value, int replace)
{
	int		index;
	char	*new_line;
	int		line_len;
	int		ret;

	if (!global->env || !name || !value)
		return (-1);
	ret = 0;
	index = find_env_index(name, global->env);
	line_len = ft_strlen(name) + ft_strlen(value) + 2;
	new_line = ft_strdupcat(name, '=', value, line_len);
	if (index == -1)
	{
		ret = put_env(global, new_line);
		ft_strdel(&new_line);
		return (ret);
	}
	if (index != -1 && replace == 1)
	{
		free(global->env[index]);
		global->env[index] = ft_strdupcat(name, '=', value, line_len);
	}
	ft_strdel(&new_line);
	return (ret);
}

/*
** we look for the index of the key
** and we concatenate the value after the current value
*/

int	set_env_append(t_global *global, char *name, char *to_add)
{
	int		len;
	char	*current_value;
	char	*new_value;

	current_value = get_env(name, global->env);
	len = ft_strlen(current_value) + ft_strlen(to_add);
	new_value = ft_calloc((len + 1), sizeof(char));
	if (!new_value)
		return (0);
	if (current_value)
		new_value = ft_strcpy(new_value, current_value);
	new_value = ft_strcat(new_value, to_add);
	set_env(global, name, new_value, 1);
	ft_strdel(&new_value);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:24:45 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/19 17:35:38 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	free_key_value(char *key, char *value, int ret)
{
	ft_strdel(&value);
	ft_strdel(&key);
	return (ret);
}

/*
** we add a new variable (key+value) if the syntax is ok
** if the key already exists and we have '+=' , we concatenate
** if export command is in a pipe sequence, we don't execute it
*/

static int	add_var(t_global *global, char *arg)
{
	int		key_size;
	int		ret;
	char	*key;
	char	*value;

	key_size = get_key_len(arg);
	key = get_key(arg, key_size);
	value = get_value(arg);
	ret = 1;
	ret = check_key_syntax(key);
	if (global->piping_index > 1)
		return (free_key_value(key, value, ret));
	if (!value)
		value = ft_strdup("");
	if (ret == 2)
	{
		key[key_size - 1] = '\0';
		if (find_env_index(key, global->env) != -1)
			set_env_append(global, key, value);
		else
			set_env(global, key, value, 0);
	}
	else if (ret == 1)
		set_env(global, key, value, 1);
	return (free_key_value(key, value, ret));
}

/*
** we add a key if the key doesn't already exist and the syntax is ok
** if export command is in a pipe sequence, we don't execute it
*/

static int	add_key(t_global *global, char *arg)
{
	int		ret;
	int		size;

	ret = check_key_syntax(arg);
	size = 0;
	if (ret == 1 && (find_env_index(arg, global->env) == -1))
	{
		size = len_env(global->env);
		if (global->piping_index <= 1)
			global->env = resize_env_add(global->env, size + 1, arg);
		if (!global->env)
			ret = 0;
	}
	return (ret);
}

/*
** we check arguments :
**  - if there is '=', we add key+value (value empty if nothing after '=')
**  - else we add a key without value
*/

static int	check_arg(t_global *global, char *arg)
{
	int	ret;

	ret = 1;
	if (ft_strchr(arg, '='))
		ret = add_var(global, arg);
	else
		ret = add_key(global, arg);
	return (ret);
}

/*
** builtin export without option
** if no argument, display the variables sorted in ascii order
*/

int	builtin_export(t_global *global, char **arg)
{
	int		i;
	int		ret;

	ret = 0;
	if (!arg[1])
		print_sorted_env(global->env);
	i = 1;
	while (arg[i])
	{
		if (!check_arg(global, arg[i]))
			ret = 1;
		i++;
	}
	return (ret);
}

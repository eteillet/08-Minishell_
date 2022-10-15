/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:07:17 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/04 22:33:27 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	prompt_error(char *msg, char *arg, int ret)
{
	ft_putstr_fd("bash: exit: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(" : ", 2);
	}
	ft_putendl_fd(msg, 2);
	return (ret);
}

static long long int	ft_atoi_long(char *str)
{
	int				i;
	int				sign;
	long long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	check_arg(char **arg, t_global *global)
{
	int	i;

	i = 0;
	if (arg[1][i] == '-' || arg[1][i] == '+')
		i++;
	while (arg[1][i])
	{
		if (arg[1][i] < '0' || arg[1][i] > '9')
		{
			global->run = false;
			global->exit_code = 2;
			return (prompt_error("argument numerique necessaire", arg[1], 0));
		}
		i++;
	}
	if (arg[2])
	{
		global->exit_code = 1;
		return (prompt_error("trop d'arguments", NULL, 0));
	}
	return (1);
}

static int	check_exit_arg(t_global *glob, long long int nb, char *arg)
{
	char	last;
	int		i;

	if (ft_strlen(arg) == 0)
		return (1);
	last = arg[ft_strlen(arg) - 1];
	i = nb % 10;
	if (i < 0)
		i *= -1;
	if ((last - '0') != i || (nb < 0 && !ft_strchr(arg, '-')))
	{
		glob->exit_code = 2;
		return (prompt_error("argument numerique necessaire", arg, 0));
	}
	return (1);
}

/*
** builtin exit without option
** exit code has to be between 0 ans 256
*/

int	builtin_exit(t_global *global, char **arg)
{
	long long int	exit_arg;

	exit_arg = 0;
	if (arg[1])
	{
		if (!(check_arg(arg, global)))
			return (1);
		exit_arg = ft_atoi_long(arg[1]);
		if (!(check_exit_arg(global, exit_arg, arg[1])))
			return (1);
	}
	global->run = false;
	if ((exit_arg == 0 && arg[1]) || exit_arg != 0)
		global->exit_code = (unsigned char)exit_arg;
	return (0);
}

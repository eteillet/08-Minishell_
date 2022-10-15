/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:57:49 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 14:59:47 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*fill_str(char *src, int size)
{
	char	*new;

	new = ft_calloc((size + 1), sizeof(char));
	if (!new)
		return (NULL);
	ft_memcpy(new, src, size);
	new[size] = '\0';
	return (new);
}

/*
** we cut the exec to get for example :
** array[0] = /bin/ and array[1] = ls
*/

static char	**split_exec(char *str, int i)
{
	char	**array;
	bool	found_slash;

	found_slash = false;
	array = (char **)malloc(sizeof(char *) * 3);
	if (!array)
		return (NULL);
	array[2] = NULL;
	while (str[i++])
	{
		if (str[i] == SLASH && is_last_char_in_str(str, i, SLASH))
		{
			found_slash = true;
			i++;
			break ;
		}
	}
	if (found_slash == false)
		i--;
	array[0] = fill_str(str, i);
	if ((ft_strlen(str) - i) > 0)
		array[1] = fill_str(&str[i], (ft_strlen(str) - i));
	else
		array[1] = ft_strdup("");
	return (array);
}

int	check_cmd(char *exec)
{
	int		ret;
	char	**split;
	int		i;

	ret = 1;
	i = 0;
	split = split_exec(exec, i);
	if (!split)
		ret = 0;
	if (!test_path(split[0], split[1]))
		ret = 0;
	free_split(split);
	return (ret);
}

/*
** we check that :
**      - it's an ordinary file (S_ISREG)
**      - we have the execution rights (S_IXUSR)
**      - it's not a directory (S_ISDIR)
*/

int	check_exec(char *exec)
{
	struct stat		bufstat;
	int				res;

	ft_memset(&bufstat, 0, sizeof(stat));
	bufstat.st_mode = 0;
	res = stat(exec, &bufstat);
	if (res == 0 && S_ISREG(bufstat.st_mode))
	{
		if (bufstat.st_mode & S_IXUSR)
			return (1);
		else if (S_ISDIR(bufstat.st_mode))
			return (0);
	}
	return (0);
}

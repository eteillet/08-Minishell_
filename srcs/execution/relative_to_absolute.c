/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative_to_absolute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:00:16 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 15:01:57 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*cut_exec(char *exec, char **ext, int *ret)
{
	char	*path;
	int		i;

	i = 0;
	path = ft_calloc(1, sizeof(char));
	while (exec[i])
	{
		path = add_c_to_str(path, exec[i]);
		if (exec[i] == '/' && is_last_char_in_str(exec, i, '/'))
		{
			i++;
			*ext = ft_calloc(1, sizeof(char));
			while (exec[i])
			{
				*ext = add_c_to_str(*ext, exec[i]);
				i++;
			}
			break ;
		}
		i++;
	}
	if (!(*ext))
		*ret = 0;
	return (path);
}

static void	free_restore(char *rel, char *abs, char *ext, char *init_dir)
{
	ft_strdel(&rel);
	ft_strdel(&abs);
	ft_strdel(&ext);
	chdir(init_dir);
	ft_strdel(&init_dir);
}

/*
** we transform the relative path into an absolute path
**      - we save the current working directory
**      - we delete the filename to keep only the folder path
**      - we access the directory
**      - we save the absolute path
**      - we go back to the initial working directory
*/

int	rel_to_abs(t_parser *parser, char *exec)
{
	int		ret;
	char	*initial_dir;
	char	*rel_path;
	char	*abs_path;
	char	*exec_ext;

	exec_ext = NULL;
	ret = 1;
	initial_dir = getcwd(NULL, 0);
	if (!initial_dir)
		ret = 0;
	rel_path = cut_exec(exec, &exec_ext, &ret);
	if (chdir(rel_path) == -1)
	{
		ft_putendl_fd("error chdir", 2);
		ret = 0;
	}
	abs_path = getcwd(NULL, 0);
	abs_path = add_c_to_str(abs_path, '/');
	parser->exec_bin = ft_strjoin(abs_path, exec_ext);
	if (!parser->exec_bin)
		ret = 0;
	free_restore(rel_path, abs_path, exec_ext, initial_dir);
	return (ret);
}

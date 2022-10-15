/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:32:01 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/23 09:18:14 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
** open the current dir (opendir)
** check it to find the executable and move to the next one (readdir)
** in the struct dirent, d_name is the name of the current file
*/

int	test_path(char *directory, char *exec)
{
	DIR				*current_dir;
	struct dirent	*content;

	current_dir = opendir(directory);
	if (!current_dir)
		return (0);
	content = readdir(current_dir);
	while (content)
	{
		if (!ft_strcmp(content->d_name, exec))
		{
			(void)closedir(current_dir);
			return (1);
		}
		content = readdir(current_dir);
	}
	(void)closedir(current_dir);
	return (0);
}

static void	set_errno_and_free_path_list(char **path_list, int ret)
{
	if (ret)
		errno = 0;
	free_split(path_list);
}

static int	concat_path_and_exec(t_parser *parser, char *path, char *exec)
{
	char	*tmp_path;

	tmp_path = ft_strdup(path);
	if (tmp_path[ft_strlen(tmp_path) - 1] != '\'')
		tmp_path = add_c_to_str(tmp_path, '/');
	parser->exec_bin = ft_calloc((ft_strlen(tmp_path) + ft_strlen(exec) + 1),
			sizeof(char));
	if (!parser->exec_bin)
		return (0);
	parser->exec_bin = ft_strcpy(parser->exec_bin, tmp_path);
	parser->exec_bin = ft_strcat(parser->exec_bin, exec);
	ft_strdel(&tmp_path);
	return (1);
}

/*
** try to find the executable in the PATH list
** if we find it and it works (test_path())
** we concatenate the path + / + exec in parser->exec_bin
*/

int	find_path(char **env, t_parser *parser, char *exec)
{
	char	*paths;
	char	**path_list;
	int		i;
	int		ret;

	ret = 0;
	paths = get_env("PATH", env);
	if (paths == NULL)
		return (ret);
	path_list = ft_split(paths, ':');
	if (path_list == NULL)
		return (ret);
	i = 0;
	while (path_list[i])
	{
		if (test_path(path_list[i], exec))
		{
			ret = concat_path_and_exec(parser, path_list[i], exec);
			if (!ret)
				break ;
		}
		i++;
	}
	set_errno_and_free_path_list(path_list, ret);
	return (ret);
}

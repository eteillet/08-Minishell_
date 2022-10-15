/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:27:44 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/05 16:37:45 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** we save the size of the history at launch of the program (if exists)
*/

static int	define_histo_len_and_index(t_global *global)
{
	int		nb_line;
	int		i;
	int		fd;
	char	buffer[4096];

	nb_line = 0;
	i = 0;
	fd = open(global->histo_path, O_RDONLY);
	if (fd < 0)
		return (0);
	while (read(fd, &(buffer[i]), 1) != 0)
	{
		if (buffer[i] == '\n')
			nb_line++;
		i++;
	}
	nb_line--;
	close(fd);
	global->size_histo = nb_line++;
	return (nb_line);
}

/*
** from 2000 bytes, we reset the history to avoid segfault
*/

static void	reset_histo_if_too_big(char *path)
{
	struct stat		bufstat;
	int				res;
	int				fd;

	ft_memset(&bufstat, 0, sizeof(stat));
	res = stat(path, &bufstat);
	fd = -1;
	if (res == 0 && bufstat.st_size > 2000)
	{
		fd = open(path, O_WRONLY | O_TRUNC);
		if (fd != -1)
			close(fd);
	}
}

/*
** reset the history if necesary
** save the new input in the history
** calculate its new size
*/

int	save_line_history(t_global *global, char *path, char *line)
{
	int		fd;

	fd = -1;
	reset_histo_if_too_big(path);
	fd = open(path, O_WRONLY | O_APPEND);
	if (fd == -1)
		return (0);
	if (!line || !line[0])
	{
		close(fd);
		return (0);
	}
	ft_putendl_fd(line, fd);
	close(fd);
	global->index_histo = define_histo_len_and_index(global);
	return (1);
}

/*
** create the history if it doesn't already exist
*/

static void	create_histo(char *path)
{
	int		fd;

	fd = -1;
	reset_histo_if_too_big(path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		fd = open(path, O_CREAT | O_RDWR, 0644);
	if (fd != -1)
		close(fd);
}

/*
** we define the path of the file which contains the history of commands
*/

void	init_history(t_global *global)
{
	char	*home;
	char	*current_dir;

	global->histo_path = NULL;
	current_dir = getcwd(NULL, 0);
	home = get_env("HOME", global->env);
	if (home)
		global->histo_path = ft_strjoin(home, "/.42_minishell_history");
	else if (current_dir)
		global->histo_path = ft_strjoin(current_dir, "/.42_minishell_history");
	ft_strdel(&current_dir);
	if (!global->histo_path)
		return ;
	create_histo(global->histo_path);
	global->index_histo = define_histo_len_and_index(global);
}

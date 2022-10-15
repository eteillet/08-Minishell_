/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:20:15 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 17:21:53 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*fill_next_line(int fd, int i, char c)
{
	char	*fill;
	char	buffer[4096];
	int		start;

	start = 0;
	fill = NULL;
	fill = malloc(sizeof(char));
	if (!fill)
		return (NULL);
	fill[0] = '\0';
	if (i == 0)
		fill = add_c_to_str(fill, c);
	while (read(fd, &(buffer[i]), 1) != 0)
	{
		if (buffer[i] == '\n')
			start++;
		else if (start == 0)
			fill = add_c_to_str(fill, buffer[i]);
		i++;
	}
	return (fill);
}

static char	*search_histo(t_global *global, int index)
{
	int		i;
	int		match;
	int		fd;
	char	buffer[4096];
	char	*new;

	i = 0;
	match = 0;
	new = NULL;
	fd = open(global->histo_path, O_RDWR);
	if (fd < 0)
		return (0);
	while (read(fd, &(buffer[i]), 1) != 0)
	{
		if (buffer[i] == '\n')
			match++;
		if (match == index)
		{
			new = fill_next_line(fd, i, buffer[i]);
			break ;
		}
		i++;
	}
	close(fd);
	return (new);
}

static void	restore_new_line(t_global *glob, char **line,
				char *new, bool len_stdin)
{
	restore_cursor_position(glob->tcaps);
	glob->cnt_stdin += 3;
	clear_line(glob->cnt_stdin, glob->tcaps);
	free(*line);
	*line = ft_strdup(new);
	ft_putstr_fd("$  ", 1);
	ft_putstr_fd(*line, 1);
	if (len_stdin)
		glob->cnt_stdin = ft_strlen(*line);
	else
		glob->cnt_stdin = 0;
}

void	up_histo(t_global *global, char *buf, char **line)
{
	char	*up;

	up = NULL;
	global->index_histo--;
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65
		&& global->index_histo <= global->size_histo)
	{
		up = search_histo(global, global->index_histo);
		if (!up)
		{
			global->index_histo++;
			return ;
		}
		restore_new_line(global, line, up, TRUE);
		free(up);
	}
	else
		global->index_histo++;
}

/*
** go down in the history toward most recent commands
** if we find a command, we replace line by this command and display it
** if we reach to the end of command list,
** we display the line which was being written
*/

void	down_histo(t_global *global, char *buf, char **line)
{
	char	*down;

	down = NULL;
	global->index_histo++;
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66
		&& global->index_histo <= global->size_histo)
	{
		down = search_histo(global, global->index_histo);
		if (!down)
		{
			global->index_histo--;
			return ;
		}
		restore_new_line(global, line, down, TRUE);
		free(down);
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66
		&& global->index_histo == global->size_histo + 1)
		restore_new_line(global, line, "", FALSE);
	else
		global->index_histo--;
}

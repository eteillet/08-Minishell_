/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:52:07 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 15:54:02 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** void ft_putchar modified in int to send to tputs
*/

int	ft_putchar_stdout(int c)
{
	write(0, &c, 1);
	return (c);
}

static void	free_line_and_clear_buf(char **line, char *buf)
{
	free(*line);
	*line = NULL;
	buf[0] = '\0';
}

static int	ctrl_d(t_global *global, char **line, char *buf, int ret)
{
	free_line_and_clear_buf(line, buf);
	ft_putstr_fd("exit\n", 2);
	global->run = false;
	return (ret);
}

static void	ctrl_c(t_global *global, char **line)
{
	free(*line);
	*line = NULL;
	g_signal = false;
	global->exit_code = errno;
}

/*
** we check the char that has just been read
** buf[0] = 4		->	ctrl-d	->	end the program
** buf[0] = 27		->	del		->	delete last char
** buf[0] = 9		->	tab		->	we ignore it
** buf[0] = 27		->	escape	->	we ignore it
** len(buf) = 3	->	escape sequence	-> check :
** 	- if it's up or down, we navigate in history :
**		- up = we decremente the index to go up in history
**		- down = we decremente the index to go down in history
*/

int	check_move(t_global *global, char *buf, char **line)
{
	if (g_signal == true)
		ctrl_c(global, line);
	if (buf[0] == 4)
	{
		if (!*line || ft_strlen(*line) == 0)
			return (ctrl_d(global, line, buf, 0));
		buf[0] = '\0';
	}
	else if (ft_strlen(buf) == 3 || buf[0] == 9 || buf[0] == 27)
	{
		up_histo(global, buf, line);
		down_histo(global, buf, line);
		buf[0] = '\0';
	}
	else if (ft_strlen(buf) == 1 && buf[0] == 127)
		del_last_char(global, buf, *line);
	else if (ft_strlen(buf) == 1 && buf[0] != 127 && buf[0] != 4)
	{
		ft_putstr_fd(&buf[0], STDOUT_FILENO);
		global->cnt_stdin++;
	}
	return (1);
}

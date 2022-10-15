/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_char_or_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:18:29 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 17:18:49 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** save the cursor position
*/

void	save_cursor_position(t_termcaps *tcaps)
{
	tputs(tcaps->save_pos, 1, ft_putchar_stdout);
}

/*
** restore the cursor position and clear the screen after the cursor
*/

void	restore_cursor_position(t_termcaps *tcaps)
{
	tputs(tcaps->rest_pos, 1, ft_putchar_stdout);
	tputs(tcaps->clr_after, 1, ft_putchar_stdout);
}

/*
** we go back to the start of the line and erase it
*/

void	clear_line(int cnt, t_termcaps *tcaps)
{
	while (cnt--)
		tputs(tcaps->left, 1, ft_putchar_stdout);
	tputs(tcaps->left, 1, ft_putchar_stdout);
	tputs(tcaps->clr, 1, ft_putchar_stdout);
}

/*
** we erase the last char of the line and on the screen
*/

void	del_last_char(t_global *global, char *buf, char *line)
{
	int	index_to_del;

	index_to_del = 0;
	if (global->cnt_stdin > 0)
	{
		tputs(global->tcaps->left, 1, ft_putchar_stdout);
		tputs(global->tcaps->clr, 1, ft_putchar_stdout);
		if (line && ft_strlen(line) >= 1)
		{
			while (line[index_to_del] != '\0')
				index_to_del++;
			line[index_to_del - 1] = '\0';
		}
		global->cnt_stdin--;
	}
	buf[0] = '\0';
}

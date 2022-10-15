/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:35:16 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 15:40:38 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*init_key(int key)
{
	static char	up[] = {27, 91, 65, 0};
	static char	down[] = {27, 91, 66, 0};
	static char	left[] = {27, 91, 68, 0};
	static char	right[] = {27, 91, 67, 0};

	if (key == 0)
		return (up);
	if (key == 1)
		return (down);
	if (key == 2)
		return (left);
	if (key == 3)
		return (right);
	return (NULL);
}

/*
** we init 2 struct termios :
**		- new_termios : to read the stdin and manage behavior
**						char by char thanks to termcaps
**		- old_termios : to restore the default behavior
**						during a fork process
** tcsetattr : we set the terminal in parameter
**
** init useful keys to manage the terminal
**
** c_lflag &= ~(ICANON); 	-> non canonical mode
** c_lflag &= ~(ECHO); 		-> deactivate echo read
** c_cc[VMIN] = 1;	-> minim nb of char when reading in non canon mode with read
** c_cc[VTIME] = 0;	-> time limit for a reading in non canonical mode with read
*/

static void	init_keys(t_termcaps *tcaps)
{
	tcgetattr(0, &(tcaps->old_termios));
	tcgetattr(0, &(tcaps->new_termios));
	tcaps->new_termios.c_lflag &= ~(ICANON);
	tcaps->new_termios.c_lflag &= ~(ECHO);
	tcaps->new_termios.c_cc[VMIN] = 1;
	tcaps->new_termios.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &tcaps->new_termios);
	tcaps->up = init_key(0);
	tcaps->down = init_key(1);
	tcaps->left = init_key(2);
	tcaps->right = init_key(3);
	tcaps->mov = tgetstr("cm", NULL);
	tcaps->clr = tgetstr("ce", NULL);
	tcaps->clr_after = tgetstr("cd", NULL);
	tcaps->del_back = tgetstr("bc", NULL);
	tcaps->del_char = tgetstr("dc", NULL);
	tcaps->del_line = tgetstr("dl", NULL);
	tcaps->save_pos = tgetstr("sc", NULL);
	tcaps->rest_pos = tgetstr("rc", NULL);
}

/*
** we init the Termcap library with tgetent
*/

static t_termcaps	*init_termcaps(char **env)
{
	t_termcaps	*tcaps;
	char		*term_name;
	int			ret;

	tcaps = malloc(sizeof(t_termcaps));
	if (!tcaps)
		return (NULL);
	term_name = get_env("TERM", env);
	if (!term_name)
	{
		ft_putendl_fd("TERM must be set in the environment to init termcaps",
			2);
		return (NULL);
	}
	ret = tgetent(NULL, term_name);
	if (ret != 1)
	{
		ft_putendl_fd("Error termcaps", 2);
		return (NULL);
	}
	else
		init_keys(tcaps);
	return (tcaps);
}

int	termcaps(t_global *global)
{
	global->tcaps = init_termcaps(global->env);
	return (1);
}

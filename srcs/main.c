/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:02:13 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/21 11:02:32 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool g_signal;
/*
** return :
**		- true if we found a '\n'
*/

static bool	is_line(char **line)
{
	char	*new_line;
	char	*sub_string;
	size_t	line_end;

	new_line = NULL;
	new_line = ft_strchr(*line, NEWLINE);
	if (new_line != NULL)
	{
		line_end = new_line - *line;
		sub_string = ft_substr(*line, 0, line_end);
		*line = ft_strreplace(*line, sub_string);
		ft_strdel(&sub_string);
		return (true);
	}
	return (false);
}

/*
** read the input char by char
** if we get a normal char, we display it
** if not we check if it's an escape sequence
** return 1 if the line is finished (newline found)
*/

static int	readline_minishell(t_global *global, char **line)
{
	int		bytes_read;
	char	buffer[BUFSIZE_READLINE + 1];
	int		ret;

	*line = NULL;
	ret = 0;
	g_signal = false;
	save_cursor_position(global->tcaps);
	bytes_read = read(STDIN_FILENO, buffer, BUFSIZE_READLINE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		ret = check_move(global, buffer, &(*line));
		*line = ft_strjoindelone(*line, buffer);
		if (!(*line))
			return (0);
		if (is_line(line))
			return (1);
		if (ret == 0)
			return (0);
		bytes_read = read(STDIN_FILENO, buffer, BUFSIZE_READLINE);
	}
	return (1);
}

/*
** we read the line and we send it to the lexer
** we save each input in the history
*/

static int	loop(t_lexer *lex, t_global *global)
{
	int		ret;
	char	*line;

	ret = 1;
	global->run = true;
	line = NULL;
	termcaps(global);
	init_history(global);
	while (ret)
	{
		prompt(global->env);
		global->cnt_stdin = 0;
		treat_signal();
		ret = readline_minishell(global, &line);
		if (!line)
			break ;
		if (ret && line[0] != '\0')
			lex_and_parse(lex, line, global);
		reset_lexer_struct(lex);
		save_line_history(global, global->histo_path, line);
		ft_strdel(&line);
		if (!global->run)
			break ;
	}
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	int			ret;
	t_global	*global;
	t_lexer		*lex;

	(void)argc;
	(void)argv;
	ret = 0;
	global = init_global_struct();
	lex = init_lexer_struct();
	save_env(global, envp);
	set_shlvl_and_default_env(global);
	loop(lex, global);
	ret = global->exit_code;
	ft_free(lex, global);
	return (ret);
}

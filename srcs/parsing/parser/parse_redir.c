/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:11:51 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/05 16:11:53 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
** open the file and return 0 if error during opening the file
*/

static int	redir_file(t_tok_type type, t_parser *parser, char *filename)
{
	t_file	*file;
	int		mode;

	if (type == TOK_INPUT)
	{
		file = &(parser->input);
		mode = O_RDONLY;
	}
	else
	{
		file = &(parser->output);
		if (type == TOK_APPEND)
		{
			parser->append = true;
			mode = O_WRONLY | O_APPEND | O_CREAT;
		}
		else
			mode = O_WRONLY | O_CREAT | O_TRUNC;
	}
	file->name = filename;
	file->fd = open(filename, mode, 0644);
	if (file->fd == -1)
		return (0);
	return (1);
}

static void	prompt_error_redir(t_global *global, char *msg, int ret)
{
	ft_putendl_fd(msg, 2);
	if (ret != -1)
		global->exit_code = ret;
}

/*
** parse redirections : input, output et append
** also process the next token (the file)
*/

int	parse_redir(t_global *glob, int i, t_token **tok, int ind_tok)
{
	int	ret;

	if (!tok[ind_tok + 1])
	{
		stop_exec_and_prompt_error(glob,
			"bash: erreur de syntaxe pres du symbole inattendu << newline >>",
			NULL, 2);
		return (0);
	}
	ret = redir_file(tok[ind_tok]->type,
			&(glob->parser[i]), tok[ind_tok + 1]->value);
	if (!ret)
	{
		prompt_error_redir(glob,
			"Aucun fichier ou dossier de ce type", 1);
		return (0);
	}
	return (1);
}

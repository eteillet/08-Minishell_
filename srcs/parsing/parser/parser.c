/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 10:44:08 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/04 22:54:09 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
** define a pipe type only if there is not the last token
*/

static void	parse_pipe(t_global *glob, int i, t_token **token, int tok)
{
	if (token[tok + 1])
		glob->parser[i].pipe = true;
}

/*
** if the next token is start, we go to the next command
*/

static int	inc_cmd(t_token **token, int tok)
{
	if (tok == 0 || token[tok - 1]->type != TOK_INPUT)
		return (1);
	return (0);
}

/*
** parse tokens and store them in the parser structure
**
** after parse_redir() we skip the next token (the file)
** i += inc_cmd  -> we go to the next command
** if it's the last token we break
*/

static void	parse_tok(t_global *glob, t_lexer *lex, int tok, size_t i)
{
	while (i <= lex->nb_cmd && lex->nb_cmd != 0)
	{
		if (lex->token[tok]->error_expand == TRUE
			&& !ft_strcmp(lex->token[tok]->value, ""))
			tok += 0;
		else if (lex->token[tok]->type == TOK_INPUT
			|| lex->token[tok]->type == TOK_OUTPUT
			|| lex->token[tok]->type == TOK_APPEND)
		{
			if (!(parse_redir(glob, i, lex->token, tok)))
				break ;
			tok++;
		}
		else if (lex->token[tok]->type == TOK_PIPE)
			parse_pipe(glob, i, lex->token, tok);
		else if (lex->token[tok]->start == true)
			parse_executable(glob, i, lex->token[tok]);
		else
			parse_str(glob, i, lex->token[tok]);
		if (tok < lex->index - 1 && lex->token[tok + 1]->start == TRUE)
			i += (size_t)inc_cmd(lex->token, tok);
		if (tok == lex->index - 1)
			break ;
		tok++;
	}
}

static void	merge_exec_and_argv(t_global *global, int nb_cmd)
{
	int	i;

	i = 0;
	while (i <= nb_cmd)
	{
		free(global->parser[i].args_for_execve);
		global->parser[i].args_for_execve
			= add_str_to_beginning_array(global->parser[i].exec,
				global->parser[i].argv);
		i++;
	}
}

/*
** debug : print_parser_struct(global, lex->nb_cmd);
*/

void	parser(t_lexer *lex, t_global *global)
{
	parse_tok(global, lex, lex->start_tok, 0);
	merge_exec_and_argv(global, lex->nb_cmd);
}

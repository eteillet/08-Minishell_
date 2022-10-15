/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_and_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 10:00:39 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/05 09:13:42 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** depending on the type of the char that is read
** we create the corresponding token
** return the nb of char that have been read to create the token
** (quotes included)
*/

static int	get_next_token(t_global *glob, t_lexer *lex, char *line, int i)
{
	int	count;

	count = 0;
	if (is_space(line[i]))
		count++;
	else if (line[i] == COMMENT && (i == 0 || (i > 0 && is_space(line[i - 1]))))
		count += create_comment_tok(line, i);
	else
	{
		init_token(lex);
		if (line[i] == BACKSLASH)
			count += skip_backslash_begin(lex->token[lex->index], line, &i);
		if (is_operator(line, i) != 0
			&& !ft_strcmp(lex->token[lex->index]->value, ""))
			count += create_operator_tok(lex, lex->token[lex->index], line, i);
		else
			count += create_string_tok(glob, lex->token[lex->index], line, i);
		if (is_first_token(lex, lex->index, line))
			lex->cmd_found = true;
		lex->index++;
	}
	return (count);
}

/*
** read a block char by char to get the tokens
** if the maximum capacity of the token** is reached, we increase it
** when we arrive to the end of the block we break
*/

static void	tokenize(t_global *global, t_lexer *lex, char *input)
{
	lex->cmd_found = false;
	while (input[lex->pos])
	{
		if (lex->index == ((int)lex->token_capacity - 1))
			lex->token = initial_lexer_is_not_enough(lex);
		lex->pos += get_next_token(global, lex, input, lex->pos);
		if (lex->pos > (int)ft_strlen(input))
			break ;
	}
}

/*
** we check that we don't have 2 operators side by side
*/

static void	check_bash_syntax_error(t_global *glob, t_token **tok, int i)
{
	if (tok[0] && tok[0]->type == TOK_PIPE)
		stop_exec_and_prompt_error(glob, "bash", tok[0]->value, 2);
	while (tok[i])
		i++;
	i--;
	while (i > 0)
	{
		if (tok[i]->type == TOK_PIPE || tok[i]->type == TOK_INPUT
			|| tok[i]->type == TOK_OUTPUT || tok[i]->type == TOK_APPEND)
		{
			tok[i]->start = false;
			if (tok[i - 1]->type == TOK_PIPE || tok[i - 1]->type == TOK_INPUT
				|| tok[i - 1]->type == TOK_OUTPUT
				|| tok[i - 1]->type == TOK_APPEND)
			{
				if (tok[i]->type == TOK_PIPE)
					stop_exec_and_prompt_error(glob, "bash", tok[i]->value, 2);
				else
					stop_exec_and_prompt_error(glob, "bash", "newline", 2);
			}
		}
		i--;
	}
}

/*
** count the nb of commands to execute
*/

int	is_redir(t_tok_type type)			/***/
{
	return (type == TOK_INPUT || type == TOK_OUTPUT || type == TOK_APPEND);
}

static size_t	count_array_token(t_token **tok, int start_index)
{
	int		i;
	size_t	size;
	bool 	redir;						/***/

	redir = false;						/***/
	i = start_index;
	size = 0;
	if (tok && tok[i])
	{
		while (tok[i])
		{
			if (tok[i]->start == true)
				size++;
			if (is_redir(tok[i]->type))	/***/
				redir = true;			/***/
			i++;
		}
	}
	if (size == 0 && redir == true)		/***/
		size = 1;						/***/
	return (size);
}

/*
** we read the line block by block (separated by ';')
** for each block :
**      - we tokenize
**      - we parse
**      - we execute the command
**      - we continue until the end of the input line
** debug : print_lexer_struct(lex);
*/

void	lex_and_parse(t_lexer *lex, char *line, t_global *global)
{
	int	i;

	i = 0;
	lex->start_tok = 0;
	global->fatal_error = false;
	lex->inputs = split_shell(global, line, ';', 0);
	lex->line = ft_strdup(line);
	while (lex->inputs[i])
	{
		global->last_ret = global->exit_code;
		lex->pos = 0;
		tokenize(global, lex, lex->inputs[i]);
		check_bash_syntax_error(global, lex->token, 0);
		is_builtin_else_exec(lex);
		lex->nb_cmd = count_array_token(lex->token, lex->start_tok);
		init_parser_struct(global, lex->nb_cmd);
		if (!(global->fatal_error) && global->run)
			parser(lex, global);
		if (!(global->fatal_error) && global->run)
			manage_commands(global, lex->nb_cmd);
		if (global->parser)
			free_parser_struct(global, lex->nb_cmd);
		lex->start_tok = lex->index;
		i++;
	}
}

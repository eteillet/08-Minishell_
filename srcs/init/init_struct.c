/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:16:56 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 15:20:26 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_parser_struct(t_global *global, int nb)
{
	int	i;

	i = 0;
	global->parser = (t_parser *)malloc(sizeof(t_parser) * (nb + 1));
	if (!global->parser)
		return ;
	while (i <= nb)
	{
		global->parser[i].exec = NULL;
		global->parser[i].exec_bin = NULL;
		global->parser[i].argv = (char **)malloc(sizeof(char *));
		if (!(global->parser[i].argv))
			return ;
		global->parser[i].argv[0] = NULL;
		global->parser[i].args_for_execve = (char **)malloc(sizeof(char *));
		if (!(global->parser[i].args_for_execve))
			return ;
		global->parser[i].args_for_execve[0] = NULL;
		global->parser[i].pipe = false;
		global->parser[i].append = false;
		global->parser[i].input.name = NULL;
		global->parser[i].output.name = NULL;
		i++;
	}
}

/*
**for each line read, we reset the structure
*/

void	reset_lexer_struct(t_lexer *lex)
{
	free_lexer_struct(lex, false);
	lex->line = NULL;
	lex->pos = 0;
	lex->index = 0;
	lex->token = ft_calloc((TOKEN_CAPACITY + 1), sizeof(t_token *));
	if (!(lex->token))
		return ;
	lex->inputs = NULL;
	lex->token_capacity = TOKEN_CAPACITY;
	lex->nb_cmd = 0;
}

t_lexer	*init_lexer_struct(void)
{
	t_lexer		*lex;

	lex = (t_lexer *)malloc(sizeof(t_lexer));
	if (!lex)
		return (NULL);
	lex->line = NULL;
	lex->pos = 0;
	lex->index = 0;
	lex->token = ft_calloc((TOKEN_CAPACITY + 1), sizeof(t_token *));
	lex->inputs = NULL;
	lex->token_capacity = TOKEN_CAPACITY;
	lex->nb_cmd = 0;
	return (lex);
}

t_global	*init_global_struct(void)
{
	t_global	*global;

	global = (t_global *)malloc(sizeof(t_global));
	if (!global)
		return (NULL);
	global->env = NULL;
	global->last_ret = 0;
	global->exit_code = 0;
	return (global);
}

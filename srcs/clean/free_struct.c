/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:37:27 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/22 11:37:30 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_global_struct(t_global *global)
{
	if (global->histo_path)
		free(global->histo_path);
	if (global)
		free(global);
}

void	free_parser_struct(t_global *global, int nb_cmd)
{
	int		i;
	int		j;

	i = 0;
	while (i <= nb_cmd)
	{
		if (global->parser[i].exec)
			free(global->parser[i].exec);
		if (global->parser[i].exec_bin)
			free(global->parser[i].exec_bin);
		j = 0;
		while (global->parser[i].argv[j])
		{
			free(global->parser[i].argv[j]);
			global->parser[i].argv[j] = NULL;
			j++;
		}
		free(global->parser[i].argv);
		free(global->parser[i].args_for_execve);
		i++;
	}
	free(global->parser);
}

void	free_token(t_token **token)
{
	size_t	i;

	i = 0;
	if (token)
	{
		while (token[i])
		{
			if (token[i]->value)
				free(token[i]->value);
			if (token[i])
				free(token[i]);
			i++;
		}
		free(token);
	}
}

/*
** if all=TRUE, we are at the end of the program
** so we have to free the content of the lexer AND the structure lexer
*/

void	free_lexer_struct(t_lexer *lex, bool all)
{
	if (lex->line)
		free(lex->line);
	if (lex->token)
		free_token(lex->token);
	if (lex->inputs)
		free_split(lex->inputs);
	if (all == true)
		free(lex);
}

void	free_tcaps_struct(t_global *global)
{
	if (global->tcaps)
		free(global->tcaps);
}

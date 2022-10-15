/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_struct_content.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:41:03 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/04 22:43:55 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** debug functions
*/

void	print_lexer_struct(t_lexer *lexer)
{
	int	i;

	printf("\n"RED"------------- debug LEXER ------------------- "OFF" \n");
	if (lexer)
	{
		if (lexer->line)
			printf(""CYA"line :%s"ORG"\n", lexer->line);
		if (lexer->token)
		{
			i = 0;
			while (lexer->token[i])
			{
				printf("token[%d] ->\t", i);
				printf("value = \'%s\'\t\t", lexer->token[i]->value);
				printf("type = %d     ", lexer->token[i]->type);
				if (lexer->token[i]->start)
					printf("\t[start]");
				printf("\n");
				i++;
			}
		}
		printf("nb_commands : %zu\n", lexer->nb_cmd);
		printf("token_capacity : %zu"OFF"\n\n", lexer->token_capacity);
	}
}

void	print_parser_struct(t_global *global, int nb)
{
	int	i;
	int	j;

	printf(""RED"-------------- debug PARSER ----------------- "OFF" \n");
	i = 0;
	while (i <= nb)
	{
		printf(""CYA"CMD numero %d *******"ORG"\n", i);
		printf("exec = %s\n", global->parser[i].exec);
		j = 0;
		while (global->parser[i].argv[j])
		{
			printf("argv[%d] = %s\n", j, global->parser[i].argv[j]);
			j++;
		}
		j = 0;
		while (global->parser[i].args_for_execve[j])
		{
			printf("a_exec[%d]=%s  ", j, global->parser[i].args_for_execve[j]);
			j++;
		}
		printf("pipe = %d\n", global->parser[i].pipe);
		i++;
		printf(""OFF"\n");
	}
}

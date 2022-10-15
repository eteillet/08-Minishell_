/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:53:25 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/08 17:02:52 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/*
** function readline in main.c
*/

# define BUFSIZE_READLINE 1042

/*
** size of the array of int with the indexes of the $? to expand
*/

# define SIZE_EXPAND_TAB 1042

/*
** colors
*/

# define WTE "\033[97m"
# define YEL "\033[93m"
# define GRN "\033[92m"
# define RED "\033[31m"
# define ORG "\033[33m"
# define CYA "\033[36m"
# define OFF "\033[0m"

/*
** we initialize a nb of tokens to malloc
*/

# define TOKEN_CAPACITY 100

/*
** bash quoting and operators
*/

# define COMMENT '#'
# define BACKSLASH '\\'
# define SLASH '/'
# define SG_QUOTE '\''
# define DB_QUOTE '\"'
# define BK_QUOTE '`'
# define DOLLAR '$'
# define PIPE '|'
# define SEMICOLON ';'
# define INPUT '<'
# define OUTPUT '>'
# define NEWLINE '\n'
# define SPACE ' '

/*
** global variable to catch signal and quit if necessary
*/

extern bool	g_signal;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:54:14 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/08 17:02:27 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/*
** mov = move the cursor to the desired coordinates
** clr = clear between the cursor and the end of line
** clr_after = clear between the cursor and the end of screen
** del_back = delete last char (backspace)
** del_char = delete the next char
** del_line = delete 1 entire line
** save_pos = save the current position
** rest_pos = restore the position saved in save_pos
*/

typedef struct s_termcaps
{
	struct termios		old_termios;
	struct termios		new_termios;
	char				*mov;
	char				*clr;
	char				*clr_after;
	char				*del_back;
	char				*del_char;
	char				*del_line;
	int					col;
	int					row;
	char				*up;
	char				*down;
	char				*right;
	char				*left;
	char				*save_pos;
	char				*rest_pos;
}						t_termcaps;

typedef struct s_file
{
	char				*name;
	int					fd;
}						t_file;

typedef enum e_tok_type
{
	TOK_NULL = 0,
	TOK_TXT,
	TOK_BUILTIN,
	TOK_EXEC,
	TOK_PIPE,
	TOK_INPUT,
	TOK_OUTPUT,
	TOK_APPEND
}						t_tok_type;

/*
** error_expand = we don't put spaces on screen if
** the token is empty and we tried to expand a variable
** ind_exp = int to browse index_to_expand
** index_to_expand = array with all the indexes
** of the $? to expand (non escaped)
*/

typedef struct s_token
{
	bool				error_expand;
	char				*value;
	bool				start;
	t_tok_type			type;
	bool				end;
	int					ind_exp;
	int					index_to_expand[SIZE_EXPAND_TAB];
}						t_token;

/*
** cmd_found = put this flag as soon as we find an exec
** line = user input
** pos = position in line
** index = index of token so the nb of token at the end of the lexing
** start_tok = the index of the token which starts the next parser structure
** token = array of tokens
** inputs = array of inputs (line separated by ;
** thanks to the 'split shell' function)
** token_capacity = the size of the lexer
** nb_cmd = the nb of commands to execute
*/

typedef struct s_lexer
{
	bool				cmd_found;
	char				*line;
	int					pos;
	int					index;
	int					start_tok;
	t_token				**token;
	char				**inputs;
	size_t				token_capacity;
	size_t				nb_cmd;
}						t_lexer;

/*
** each input becomes a parser structure to execute
** exec = the executable (builtin or binary)
** exec_bin = the final executable with the path to send to execve
** argv = the arguments of the command to execute
** args_for_execve = concatenation of exec_bin and argv to send to execve
*/

typedef struct s_parser
{
	char				*exec;
	char				*exec_bin;
	char				**argv;
	char				**args_for_execve;
	bool				pipe;
	pid_t				pid;
	t_file				input;
	t_file				output;
	bool				append;
}						t_parser;

/*
** cnt_stdin = count the nb of char printed on stdin
** histo_path = the history of command is stored in a .42_minishell_history
** index_histo = on which line we are when
** we navigate in history (the last by default)
** size_histo = nb of commans in the history
** fatal_error = error which prevents the execution of the program
** run = we pass run to false when we process exit
** piping_index = the nb of successive pipes
** infile = fd of file if <
** outfile = fd of file if > or >>
*/

typedef struct s_global
{
	char				**env;
	int					cnt_stdin;
	char				*histo_path;
	int					index_histo;
	int					size_histo;
	t_termcaps			*tcaps;
	bool				fatal_error;
	bool				run;
	t_parser			*parser;
	int					piping_index;
	int					skip_piped_cmd;
	int					infile;
	int					outfile;
	int					savein;
	int					saveout;
	int					fdin;
	int					fdout;
	long int			exit_code;
	int					last_ret;
}						t_global;

#endif

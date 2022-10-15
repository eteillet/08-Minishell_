/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:02:56 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/08 17:15:03 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

/*
** builtins
*/

int			builtin_cd(t_global *global, char **arg);
int			builtin_echo(char **arg);
int			builtin_export(t_global *global, char **arg);
int			builtin_env(t_global *global, char **arg);
int			builtin_exit(t_global *global, char **arg);
int			builtin_pwd(void);
int			builtin_unset(t_global *global, char **arg);

/*
** export_sort.c && export_check_error.c
*/

void		prompt_export_error(char *key);
int			check_key_syntax(char *key);
char		*get_key(char *line, int size);
char		*get_value(char *line);
void		sort_env(char **sorted_env);
void		print_sorted_env(char **env);

/*
** clean
** free and exit the program
*/

void		free_env(char **env);
void		ft_free(t_lexer *lex, t_global *global);
void		free_global_struct(t_global *global);
void		free_parser_struct(t_global *global, int nb_cmd);
void		free_token(t_token **token);
void		free_lexer_struct(t_lexer *lex, bool all);
void		free_tcaps_struct(t_global *global);

/*
** display
*/

void		prompt(char **env);
void		stop_exec_and_prompt_error(t_global *glob,
				char *msg, char *tok, int ret);
int			error_command(t_global *glob, char *cmd, int exit, int ret);
void		print_lexer_struct(t_lexer *lex);
void		print_parser_struct(t_global *global, int nb);

/*
** environment
*/

int			find_env_index(char *name, char **env);
void		save_env(t_global *global, char **env);
char		*get_env(char *name, char **env);
int			len_env(char **env);
int			len_env_line(int i, char **env);
int			get_key_len(char *line);
void		print_env(char **env, bool export);
int			put_env(t_global *global, char *str);
int			set_env(t_global *global, char *name, char *value, int replace);
int			set_env_append(t_global *global, char *name, char *to_add);
int			unset_env(t_global *glob, char *name);
char		**resize_env_del(char **env, int size, int index_to_del);
char		**resize_env_add(char **env, int size, char *new);

/*
** execution
*/

int			check_cmd(char *exec);
int			check_exec(char *exec);
int			redir_pipe_sequence(t_global *global, int i, int j);
int			execute_builtin(t_global *glob, char **arg);
int			dispatch_cmd(t_global *glob, t_parser parser, char **arg, int i);
void		manage_commands(t_global *global, int nb_cmd);
void		save_initial_fd(t_global *global);
int			redirect_fd(int old, int new);
int			restore_initial_fd(t_global *global);
int			rel_to_abs(t_parser *parser, char *exec);

/*
** init_struct.c
*/

t_global	*init_global_struct(void);
void		init_parser_struct(t_global *global, int nb);
t_lexer		*init_lexer_struct(void);
void		reset_lexer_struct(t_lexer *lex);

/*
** lexer.c
*/

void		lex_and_parse(t_lexer *lex, char *line, t_global *global);

/*
** malloc_tokens.c
*/

t_token		*malloc_token(void);
char		*calloc_token_value(int len);

/*
** create_tokens.c
*/

void		init_token(t_lexer *lex);
int			create_comment_tok(char *line, int i);
int			create_db_quote_tok(t_global *glob, t_token *tok, char *s, int i);
int			create_sg_quote_tok(t_token *tok, char *s, int i);
int			create_operator_tok(t_lexer *lex, t_token *tok, char *s, int i);
int			create_string_tok(t_global *glob, t_token *tok, char *s, int i);

/*
** is_builtin.c
*/

int			is_builtin(char *tok);
void		is_builtin_else_exec(t_lexer *command);

/*
** duplicate_lexer.c
** if lexer is full (cf TOKEN_CAPACITY), we increase it
*/

void		copy_token(t_token *src, t_token *dest);
t_token		**initial_lexer_is_not_enough(t_lexer *lex);

/*
** escaping.c
*/

int			skip_backslash_begin(t_token *tok, char *line, int *i);
int			is_escaped(char *line, int index);
int			not_quoted_not_escaped(char *line, int index);

/*
** expansion.c
*/

int			cnt_char_before(char *s, int i, char c);
int			expand_var(t_global *global, t_token *tok, char *line, int i);

/*
** is_operator.c
*/

void		assign_type_operator(t_lexer *lex, t_token *tok);
int			is_operator(char *str, int i);

/*
** split_shell.c & split_shell_utils.c
** we split user input thanks to the ';' separator
*/

char		**split_shell(t_global *global, char *s, char c, int w);
int			nothing_before(char *str, int index, char c);
int			nothing_after(char *str, int index);
void		check_valid_semicolons(t_global *global, char *str);

/*
** utils_parsing.c
*/

int			is_space(int c);
int			only_space_before(t_lexer *lex, char *input);
int			skip_backslash_begin(t_token *tok, char *line, int *i);
int			is_first_token(t_lexer *lex, int index, char *input);

/*
** parser
*/

void		parser(t_lexer *lex, t_global *global);
void		parse_str(t_global *glob, int i, t_token *tok);
int			parse_redir(t_global *glob, int i, t_token **tok, int ind_tok);
char		*is_expand_last_ret(t_global *glob, int *tab_index, char *s, int i);
void		parse_executable(t_global *glob, int i, t_token *tok);

/*
** find_executable.c
** we check if the 1st argument is a builtin or in the environment path list
*/

int			test_path(char *directory, char *exec);
int			find_path(char **env, t_parser *parser, char *exec);
int			is_executable(char *tok);

/*
** shell_level
*/

void		set_shlvl_and_default_env(t_global *global);

/*
** signals
*/

void		control_child(int n);
void		treat_child_signal(int pid);
void		treat_signal(void);

/*
** termcaps.c
*/

int			termcaps(t_global *global);
int			ft_putchar_stdout(int c);
int			check_move(t_global *global, char *buf, char **line);
void		init_history(t_global *global);
int			save_line_history(t_global *global, char *path, char *line);
void		up_histo(t_global *global, char *buf, char **line);
void		down_histo(t_global *global, char *buf, char **line);
void		save_cursor_position(t_termcaps *tcaps);
void		restore_cursor_position(t_termcaps *tcaps);
void		clear_line(int cnt, t_termcaps *tcaps);
void		del_last_char(t_global *global, char *buf, char *line);

#endif

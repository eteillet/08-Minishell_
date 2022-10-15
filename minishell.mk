INC_FILES	=	define.h						\
				minishell.h						\
				proto.h							\
				struct.h

SRC_FILES	= 	main.c

# builtins

SRC_FILES	+=	cd.c 							\
				echo.c 							\
				env.c 							\
				exit.c 							\
				export.c 						\
				export_check_error.c			\
				export_sort.c 					\
				pwd.c 							\
				unset.c

# clean

SRC_FILES	+=	free_struct.c					\
				quit.c

# display

SRC_FILES	+=	check_struct_content.c 			\
				error.c 						\
				prompt.c

# environment

SRC_FILES	+=	find_env_index.c 				\
				get_env.c 						\
				len_env.c 						\
				print_env.c 					\
				put_env.c 						\
				resize_env.c 					\
				save_env.c 						\
				set_env.c 						\
				unset_env.c

# execution

SRC_FILES	+=	check_exec.c					\
				execute.c 						\
				manage_commands.c 				\
				manage_fd.c 					\
				redirection.c					\
				relative_to_absolute.c
				

# init

SRC_FILES	+=	init_struct.c

# parsing

SRC_FILES	+=	create_ope_and_comment_tok.c	\
				create_str_and_quote_tok.c		\
				duplicate_lexer.c 				\
				escaping.c 						\
				expansion.c 					\
				find_executable.c 				\
				init_token.c 					\
				is_builtin.c 					\
				is_operator.c 					\
				lex_and_parse.c 				\
				malloc_tokens.c 				\
				parse_exec.c 					\
				parse_last_ret_expansion.c 		\
				parse_redir.c 					\
				parse_str.c 					\
				parser.c 						\
				split_shell.c 					\
				split_shell_utils.c				\
				utils_parsing.c

# shell_level

SRC_FILES	+=	set_shlvl.c

# signal

SRC_FILES	+=	signal.c

# termcaps

SRC_FILES	+=	check_move.c 					\
				put_termcaps.c 					\
				history.c 						\
				navigate.c						\
				termcaps.c
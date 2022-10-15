/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:49:06 by eteillet          #+#    #+#             */
/*   Updated: 2021/05/04 22:25:39 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** try to match the exec with one of the builtins
*/

int	execute_builtin(t_global *glob, char **arg)
{
	int	ret;

	ret = -1;
	if (!(ft_strcmp(arg[0], "cd")))
		ret = builtin_cd(glob, arg);
	else if (!(ft_strcmp(arg[0], "echo")))
		ret = builtin_echo(arg);
	else if (!(ft_strcmp(arg[0], "env")))
		ret = builtin_env(glob, arg);
	else if (!(ft_strcmp(arg[0], "exit")))
		ret = builtin_exit(glob, arg);
	else if (!(ft_strcmp(arg[0], "export")))
		ret = builtin_export(glob, arg);
	else if (!(ft_strcmp(arg[0], "pwd")))
		ret = builtin_pwd();
	else if (!(ft_strcmp(arg[0], "unset")))
		ret = builtin_unset(glob, arg);
	if (ft_strcmp(arg[0], "exit") != 0)
		glob->exit_code = ret;
	if (ret == 0)
		errno = 0;
	return (ret);
}

/*
** we check that the executable is ok :
**      - in this format : ../bin/ls
**      - or this one : /bin/ls
**      - or this one : ls
** and to finish we check if it's a valid file (not a directory for example)
*/

static int	match_exec(t_global *glob, t_parser *parser, char *exec)
{
	if (exec[0] == '.' || exec[0] == SLASH)
	{
		if (exec[0] == '.')
			rel_to_abs(parser, exec);
		else
			parser->exec_bin = ft_strdup(exec);
		if (!check_cmd(exec))
			return (0);
	}
	else
	{
		if (!find_path(glob->env, parser, exec))
			return (0);
	}
	if (!check_exec(parser->exec_bin))
		return (0);
	return (1);
}

/*
** if the executable is valid, we execute the command
** we reactivate the default behavior of the terminal (old_termios)
** to be able to intercept ctrl-d during the execution of cat for example
*/

static int	execute_bin(t_global *global, t_parser parser, int i)
{
	pid_t	pid;
	int		ret;

	ret = 0;
	tcsetattr(0, 0, &(global->tcaps->old_termios));
	pid = fork();
	global->parser[i].pid = pid;
	if (pid > 0)
	{
		ft_strdel(&(parser.exec_bin));
	}
	else if (pid == 0)
	{
		ret = execve(parser.exec_bin, parser.args_for_execve, global->env);
	}
	if (pid < 0 || ret == -1)
	{
		global->exit_code = errno;
		ft_putendl_fd(strerror(errno), 2);
	}
	treat_child_signal((int)pid);
	return ((int)pid);
}

static void	create_path_in_cur_dir(t_parser *parser, char *current_dir)
{
	parser->exec_bin = ft_strjoin(current_dir, "/");
	parser->exec_bin = ft_strjoindelone(parser->exec_bin, parser->exec);
}

/*
** dispatch :
**	- builtin ?
**	- executable ? : in this case we return the pid of the process
**		- try to find the file in the path list
**		- try to find the file in current dir (ex: unset PATH;cd /bin;ls)
*/

int	dispatch_cmd(t_global *glob, t_parser parser, char **arg, int i)
{
	int		ret_pid;
	char	*current_dir;

	ret_pid = execute_builtin(glob, arg);
	if (ret_pid == -1)
	{
		current_dir = getcwd(NULL, 0);
		if (!match_exec(glob, &parser, parser.exec))
		{
			if (!ft_strchr(parser.exec, '/') && check_exec(parser.exec)
				&& current_dir)
				create_path_in_cur_dir(&parser, current_dir);
			else
			{
				ft_strdel(&(parser.exec_bin));
				ft_strdel(&current_dir);
				return (error_command(glob, parser.exec, 127, 0));
			}
		}
		ft_strdel(&current_dir);
		ret_pid = execute_bin(glob, parser, i);
		return (ret_pid);
	}
	return (-1);
}

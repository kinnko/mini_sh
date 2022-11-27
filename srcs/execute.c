/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:30:49 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/23 16:39:26 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern t_data	g_data;

void			set_signal_during_execute(void);

// This function only returns when execution failed.
static int	child_process(char *filepath, char **args, t_shell *shell)
{
	int	exit_code;

	if (!is_cmd(filepath))
	{
		exit_code = execve(filepath, args, shell->envp);
		if (exit_code == -1)
			perror(MINISHELL);
	}
	else
		exit_code = run_path_env_executable(filepath, args, shell->envp);
	return (exit_code);
}

static bool	is_builtin_cmd(char **args, t_shell *shell)
{
	size_t	i;

	i = 0;
	while (i < BUILTIN_CMD_COUNT)
	{
		if (strequ(shell->builtin_list[i], args[0]))
			return (true);
		i++;
	}
	return (false);
}

static void	run_executable(char *filepath, char **args, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror(MINISHELL);
		return ;
	}
	else if (pid == 0)
		exit(child_process(filepath, args, shell));
	else
	{
		set_signal_during_execute();
		if (wait(&(status)) == -1)
		{
			perror(MINISHELL);
			exit(STATUS_FAILS);
		}
		shell->exit_code = (((status) & 0xff00) >> 8);
		if (g_data.run_handler == true)
			shell->exit_code = 128 + g_data.sig_received;
	}
	return ;
}

size_t	get_pipe_i(t_strs args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		if (*args[i] == '|')
			return (i);
		i++;
	}
	return (0);
}

void	execute(char **args, t_shell *shell)
{
	size_t	pipe_char_i;
	char	*pipe_char_buf;
	int		i;

	pipe_char_i = 0;
	if (has_pipe(args))
	{
		pipe_char_i = get_pipe_i(args);
		pipe_char_buf = args[pipe_char_i];
		args[pipe_char_i] = NULL;
	}
	i = -1;
	while (args[++i] != NULL)
		args[i] = expand_vars(args[i], shell->exit_code, shell->envp);
	exclude_quote(args);
	if (is_builtin_cmd(args, shell))
		run_builtin_cmd(args, shell);
	else
		run_executable(args[0], args, shell);
	if (pipe_char_i)
		args[pipe_char_i] = pipe_char_buf;
}

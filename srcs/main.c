/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:31:01 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/23 16:12:41 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void	reset_sig(void);

bool	reset_redirects(t_shell *shell)
{
	t_redirect	*redirect;

	redirect = &(shell->redirect);
	if (dup2(redirect->std_in, STDIN) == -1)
		put_error_exit();
	if (dup2(redirect->std_out, STDOUT) == -1)
		put_error_exit();
	close(redirect->std_in);
	close(redirect->std_out);
	set_redirect(&shell->redirect);
	if (shell->redirect.std_in == -1 || shell->redirect.std_out == -1)
		put_error_exit();
	return (true);
}

// must null check
t_strs	get_args(t_shell *shell, char **line, int *exit_code)
{
	t_strs	args;

	*line = readline("minishell> ");
	if (g_data.run_handler == true && g_data.sig_received == SIGINT)
	{
		g_data.run_handler = false;
		g_data.sig_received = 0;
		*exit_code = 1;
	}
	if (*line == NULL)
	{
		close(shell->redirect.std_in);
		close(shell->redirect.std_out);
		ft_putstr_fd("exit\n", 1);
		exit(*exit_code);
	}
	if (ft_strlen(*line) > 0)
		add_history(*line);
	if (!check_quart_syntax(*line, exit_code))
		return (NULL);
	args = split_args(line);
	if (args == NULL)
		put_error_exit();
	return (args);
}

void	loop(t_shell *shell)
{
	t_strs	args;
	char	*line;

	while (1)
	{
		reset_sig();
		args = get_args(shell, &line, &(shell->exit_code));
		if (args != NULL && check_syntax(&line, &args, &(shell->exit_code))
			&& check_redirects(args, &(shell->exit_code)))
		{
			shell->pipe.in_buf = dup(STDIN);
			shell->pipe.out_buf = dup(STDOUT);
			if (shell->pipe.in_buf == -1 || shell->pipe.out_buf == -1)
				put_error_exit();
			recursive_execute(0, args, shell);
			close(shell->pipe.in_buf);
			close(shell->pipe.out_buf);
		}
		free(line);
		if (args != NULL)
			free_strs(args);
		if (!reset_redirects(shell))
			exit(STATUS_FAILS);
	}
}

void	exit_shell(t_shell *shell)
{
	close(shell->redirect.std_in);
	close(shell->redirect.std_out);
	free(shell->current_dir);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	loop(&shell);
	exit_shell(&shell);
	return (STATUS_SUCCESS);
}

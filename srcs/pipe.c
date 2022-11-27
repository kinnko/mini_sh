/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:31:03 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/23 16:15:54 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool		has_pipe(char **args);
static int	include_args(t_strs args);

bool	is_pipe(char *s)
{
	return (strequ(s, "|"));
}

void	recursive_execute(t_fd in, t_strs args, t_shell *shell)
{
	int	pipe_args[2];

	if (dup2(in, STDIN) == -1)
		put_error_exit();
	if (!has_pipe(args))
	{
		if (dup2(shell->pipe.out_buf, STDOUT) == -1)
			put_error_exit();
		execute(args, shell);
		if (dup2(shell->pipe.in_buf, STDIN) == -1)
			put_error_exit();
		close(in);
		return ;
	}
	if (pipe(pipe_args) == -1)
		put_error_exit();
	if (dup2(pipe_args[1], 1) == -1)
		put_error_exit();
	execute(args, shell);
	close(pipe_args[1]);
	close(in);
	args += include_args(args);
	recursive_execute(pipe_args[0], args, shell);
}

static int	include_args(t_strs args)
{
	int	total;

	total = 0;
	while (!(strequ(*args, "|") || *args == NULL))
	{
		args++;
		total++;
	}
	if (**args == '|')
		total++;
	return (total);
}

bool	has_pipe(char **args)
{
	while (*args != NULL)
	{
		args++;
		if (strequ(*args, "|"))
			return (true);
	}
	return (false);
}

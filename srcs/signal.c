/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:31:15 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/22 08:24:04 by yueyama          ###   ########.fr       */
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
#include <unistd.h>

t_data	g_data;

void	sig_ctrl(int sig)
{
	if (g_data.state == HEREDOC)
	{
		if (sig == SIGINT)
			g_data.run_handler = true;
	}
	else if (g_data.state == EXECUTE)
	{
		if (sig == SIGINT)
			ft_putstr_fd("\n", 2);
		else if (sig == SIGQUIT)
		{
			ft_putstr_fd("Quit; 3", 2);
			kill(0, SIGINT);
		}
	}
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_data.sig_received = sig;
	g_data.run_handler = true;
}

void	reset_sig(void)
{
	g_data.state = WAIT_COMMANDS;
	g_data.run_handler = false;
	if (signal(SIGINT, sig_ctrl) == SIG_ERR || signal(SIGQUIT,
			SIG_IGN) == SIG_ERR)
	{
		ft_putstr_fd("signal() failed\n", 2);
		exit(STATUS_FAILS);
	}
	return ;
}

void	set_signal_during_execute(void)
{
	g_data.state = EXECUTE;
	g_data.run_handler = false;
	if (signal(SIGINT, sig_ctrl) == SIG_ERR || signal(SIGQUIT,
			sig_ctrl) == SIG_ERR)
	{
		ft_putstr_fd("signal() failed\n", 2);
		exit(STATUS_FAILS);
	}
	return ;
}

void	set_signal_during_heredoc(void)
{
	g_data.state = HEREDOC;
	g_data.run_handler = false;
	if (signal(SIGINT, sig_ctrl) == SIG_ERR || signal(SIGQUIT,
			SIG_IGN) == SIG_ERR)
	{
		ft_putstr_fd("signal() failed\n", 2);
		exit(STATUS_FAILS);
	}
	return ;
}

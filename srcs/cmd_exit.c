/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:30:24 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/22 08:25:05 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void	exit_error_numeric(char *numeric)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(numeric, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

int	exit_error_too_many_args(void)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	return (STATUS_FAILS);
}

static bool	is_numeric(char *numeric)
{
	int		i;
	bool	exist_num;

	i = 0;
	exist_num = false;
	if (numeric == NULL)
		return (false);
	if (numeric[i] == '-' || numeric[i] == '+')
		++i;
	while (numeric[i] != '\0')
	{
		if (!(numeric[i] >= '0' && numeric[i] <= '9'))
			return (false);
		exist_num = true;
		i++;
	}
	if (exist_num == false)
		return (false);
	return (true);
}

int	do_exit_cmd(t_strs args, int exit_code)
{
	char	*trimed_arg;

	trimed_arg = ft_strtrim(args[1], " ");
	if (length_strs(args) == 1)
	{
		ft_putstr_fd("exit\n", 2);
		exit(exit_code);
	}
	if (is_numeric(trimed_arg) && length_strs(args) == 2)
	{
		ft_putstr_fd("exit\n", 2);
		exit((unsigned char)ft_atoi(trimed_arg));
	}
	if (!is_numeric(trimed_arg))
		exit_error_numeric(trimed_arg);
	else
	{
		free(trimed_arg);
		return (exit_error_too_many_args());
	}
	return (exit_code);
}

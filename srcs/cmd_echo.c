/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:30:17 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/22 08:31:35 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "stdio.h"

int	do_echo_cmd(char **args)
{
	bool	is_n;

	args++;
	is_n = false;
	if (strequ("-n\0", *args))
	{
		is_n = true;
		args++;
	}
	while (*args != NULL)
	{
		ft_putstr_fd(*args, 1);
		args++;
		if (*args != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (!is_n)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}

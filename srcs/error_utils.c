/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:30:39 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/23 12:30:15 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

char	**check_malloc_strs(char **strs)
{
	if (strs == NULL)
	{
		perror(MINISHELL);
		exit(STATUS_FAILS);
	}
	return (strs);
}

char	*wrap_malloc(char *str)
{
	if (str == NULL)
	{
		perror(MINISHELL);
		exit(STATUS_FAILS);
	}
	return (str);
}

t_false	export_error(char *args)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd(" : not a valid identifier\n", 2);
	return (false);
}

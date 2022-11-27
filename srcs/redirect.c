/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:31:12 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/23 15:20:19 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool	is_redirect(char *str)
{
	if (str == NULL)
		return (false);
	return ((strequ(str, ">")) || (strequ(str, ">>")) || (strequ(str, "<"))
		|| (strequ(str, "<<")));
}

bool	check_redirects(t_strs args, int *exit_code)
{
	size_t	i;
	bool	is_success;

	i = -1;
	while (args[++i] != NULL)
	{
		if (!is_redirect(args[i]))
			continue ;
		if (ft_strcmp(args[i], ">>") == 0)
			is_success = redirect_add_to(exclude_quote(&(args[i + 1]))[0]);
		else if (ft_strcmp(args[i], ">") == 0)
			is_success = redirect_to(exclude_quote(&(args[i + 1]))[0]);
		else if (ft_strcmp(args[i], "<<") == 0)
			is_success = here_docs(exclude_quote(&(args[i + 1]))[0], exit_code);
		else if (ft_strcmp(args[i], "<") == 0)
			is_success = redirect_from(exclude_quote(&(args[i + 1]))[0]);
		if (!is_success)
			return (false);
		remove_strs(args, i);
		remove_strs(args, i);
		i--;
	}
	return (true);
}

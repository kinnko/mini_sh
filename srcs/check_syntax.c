/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:30:11 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/22 21:11:01 by ainoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stddef.h>

t_false	put_syntax_error(char *str)
{
	if (str == NULL)
		str = "newline";
	if (ft_putstr_fd("minishell: syntax error near unexpected token `",
			2) == 0)
		perror(MINISHELL);
	if (ft_putstr_fd(str, 2) == 0)
		perror(MINISHELL);
	if (ft_putstr_fd("'\n", 2) == 0)
		perror(MINISHELL);
	return (false);
}

bool	check_redirect_syntax(t_strs args)
{
	size_t	i;

	i = 0;
	while (args[i] != NULL)
	{
		if (is_redirect(args[i]))
		{
			if (args[i + 1] == NULL || is_redirect(args[i + 1])
				|| is_pipe(args[i + 1]))
				return (put_syntax_error(args[i + 1]));
		}
		i++;
	}
	return (true);
}

bool	check_syntax(char **line, t_strs *args_ptr, int *exit_code)
{
	t_strs	args;

	args = *args_ptr;
	if (args[0] == NULL)
		return (false);
	if (!check_redirect_syntax(args) || !check_pipe_syntax(line, args_ptr))
	{
		*exit_code = 258;
		return (false);
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_syntax.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:30:07 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/23 11:30:50 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>

static bool	update_args(char **line, t_strs *args_ptr)
{
	char	**new_args;

	new_args = ft_split(*line, ' ');
	free_strs(*args_ptr);
	if (new_args == NULL)
		return (false);
	*args_ptr = new_args;
	return (true);
}

// must null check
static char	*ft_strjoin_space(char *s1, char *s2)
{
	char	*s1space;
	char	*s1spaces2;

	s1space = ft_strjoin(s1, " ");
	if (s1space == NULL)
		return (NULL);
	s1spaces2 = ft_strjoin(s1space, s2);
	free(s1space);
	return (s1spaces2);
}

static bool	reread(char **line, t_strs *args_ptr)
{
	char	*read;
	char	*tmp;

	while (1)
	{
		read = readline("> ");
		if (read == NULL)
			return (false);
		if (ft_strlen(read) != 0)
			break ;
		free(read);
	}
	tmp = ft_strjoin_space(*line, read);
	free(read);
	if (tmp == NULL)
		return (false);
	*line = tmp;
	return (update_args(line, args_ptr));
}

bool	check_pipe_syntax(char **line, t_strs *args_ptr)
{
	size_t	i;
	t_strs	args;

	args = *args_ptr;
	i = 0;
	if (is_pipe(*args))
		return (put_syntax_error("|"));
	while (args[i] != NULL)
	{
		if (is_pipe(args[i]) && is_pipe(args[i + 1]))
			return (put_syntax_error(args[i + 1]));
		if (is_pipe(args[i]) && args[i + 1] == NULL)
		{
			if (!reread(line, args_ptr))
			{
				if (errno != 0)
					perror(MINISHELL);
				return (false);
			}
		}
		i++;
	}
	return (true);
}

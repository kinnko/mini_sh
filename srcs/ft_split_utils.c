/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainoue <ainoue.@student.42tokyo.f>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 05:07:31 by ainoue            #+#    #+#             */
/*   Updated: 2022/10/23 05:11:41 by ainoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdbool.h>

size_t	get_word_count(char *line)
{
	bool	is_in_quart[2];
	size_t	word_count;

	if (line == NULL)
		return (0);
	word_count = 1;
	reset_is_in_quart(is_in_quart);
	while (*line != '\0')
	{
		update_quart_in(&(is_in_quart[QUART_D]), &(is_in_quart[QUART_S]),
			*line);
		if (!is_in_quart[QUART_D] && !is_in_quart[QUART_S] && *line == ' ')
		{
			word_count++;
			while (*line == ' ')
				line++;
		}
		else
			line++;
	}
	return (word_count);
}

size_t	strclen(char *str, bool *is_in_d_quart, bool *is_in_s_quart)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		update_quart_in(is_in_d_quart, is_in_s_quart, str[i]);
		if (!*is_in_s_quart && !*is_in_d_quart && str[i] == ' ')
			return (i);
		i++;
	}
	return (i);
}

void	*free_all(char **str_array, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(str_array[i]);
		i++;
	}
	free(str_array);
	return (NULL);
}

bool	is_redirect_pipe(char *str)
{
	return (is_redirect_add(str) || is_redirect_to(str) || is_redirect_from(str)
		|| is_start_pipe(str) || is_here_docs(str));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:56:07 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/23 12:30:15 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdbool.h>

// must null check
static char	**generate_split_strs(char **split_strs, char const *str)
{
	size_t	i;
	bool	is_in_q[2];

	is_in_q[QUART_S] = false;
	is_in_q[QUART_D] = false;
	i = 0;
	while (1)
	{
		while (*str == ' ' && *str != '\0')
			str++;
		if (*str == '\0')
		{
			split_strs[i] = NULL;
			return (split_strs);
		}
		split_strs[i] = ft_substr(str, 0, strclen((char *)str,
					&is_in_q[QUART_S], &is_in_q[QUART_D]));
		if (split_strs[i] == NULL)
			return (free_all(split_strs, i));
		str += strclen((char *)str, &is_in_q[QUART_S], &is_in_q[QUART_D]);
		i++;
	}
	return (split_strs);
}

size_t	get_size_inserted_space(char *line)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(line);
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i + 1] == '|')
			len++;
		if (line[i] == '|' && line[i + 1] != ' ')
			len++;
		if (line[i] != ' ' && line[i] != '>' && line[i + 1] == '>')
			len++;
		if (line[i] == '>' && line[i + 1] != ' ' && line[i + 1] != '>')
			len++;
		if (line[i] != ' ' && line[i] != '<' && line[i + 1] == '<')
			len++;
		if (line[i] == '<' && line[i + 1] != ' ' && line[i + 1] != '<')
			len++;
		i++;
	}
	return (len);
}

static void	insert_space_newline(char *new_line, size_t new_len,
		bool is_in_quart[2], char *line)
{
	size_t	i;
	size_t	new_i;

	new_i = 0;
	i = 0;
	new_line[new_i++] = line[i++];
	while (line[i] != '\0')
	{
		update_quart_in(&(is_in_quart[QUART_D]), &(is_in_quart[QUART_S]),
			line[i]);
		if (is_in_quart[QUART_D] || is_in_quart[QUART_S]
			|| !is_redirect_pipe(&line[i]))
		{
			new_line[new_i++] = line[i++];
			continue ;
		}
		if (line[i - 1] != ' ')
			new_line[new_i++] = ' ';
		if (is_redirect_add(&line[i]) || (is_here_docs(&line[i])))
			new_line[new_i++] = line[i++];
		new_line[new_i++] = line[i++];
		if (line[i - 1] != '\0' && line[i] != ' ' && new_len > new_i)
			new_line[new_i++] = ' ';
	}
	new_line[new_i++] = line[i++];
}

void	insert_space(char *new_line, size_t new_len, char *line)
{
	bool	is_in_quart[2];

	reset_is_in_quart(is_in_quart);
	insert_space_newline(new_line, new_len, is_in_quart, line);
	free(line);
}

// must null check
char	**split_args(char **str)
{
	char	**split_strs;
	size_t	new_len;
	char	*new_line;

	if (str == NULL || *str == NULL)
		return (NULL);
	if (ft_strlen(*str) >= 2)
	{
		new_len = get_size_inserted_space(*str);
		new_line = wrap_malloc((char *)malloc(sizeof(char) * (new_len
						+ 1)));
		ft_memset(new_line, '\0', new_len + 1);
		insert_space(new_line, new_len, *str);
		*str = new_line;
	}
	split_strs = (char **)malloc(sizeof(char *) * (get_word_count(*str) + 1));
	if (split_strs == NULL)
		return (NULL);
	return (generate_split_strs(split_strs, *str));
}

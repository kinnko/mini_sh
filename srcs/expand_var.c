/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:30:54 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/23 17:23:48 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char	*get_var_name(char *line)
{
	char	*var_name;
	size_t	var_name_length;

	var_name_length = 1;
	var_name = ft_strchr(line, '$');
	if (var_name == NULL)
		return (NULL);
	if (var_name[1] == '?')
		return (ft_strdup("$?"));
	while (ft_isalnum(var_name[var_name_length])
		|| var_name[var_name_length] == '_')
		var_name_length++;
	return (wrap_malloc(ft_substr(var_name, 0, var_name_length)));
}

// must null check
char	*add_after_text(char *var_name, char *var_value, char *line)
{
	while (ft_strncmp(var_name, line, ft_strlen(var_name)) != 0)
		line++;
	line += ft_strlen(var_name);
	return (ft_strjoin(var_value, line));
}

// must null check
char	*expand_var(char *line, int exit_code, t_strs envp)
{
	char	*var_name;
	char	*var_value;
	char	*new_line;

	var_name = get_var_name(line);
	if (var_name == NULL)
		return (line);
	if (ft_strncmp(var_name, "$?", 2) == 0)
		var_value = ft_itoa(exit_code);
	else
		var_value = get_value_envp(envp, var_name + 1);
	if (var_value == NULL)
		var_value = ft_strdup("");
	if (is_pipe(var_value) || is_redirect(var_value))
		new_line = wrap_malloc(ft_strjoin("\"",
					wrap_malloc(ft_strjoin(line, "\""))));
	new_line = add_after_text(var_name, var_value, line);
	free(var_name);
	free(var_value);
	return (new_line);
}

char	*expand_vars(char *line, int exit_code, t_strs envp)
{
	int		i;
	bool	is_in_quart[2];
	char	*after_var;

	i = 0;
	reset_is_in_quart(is_in_quart);
	while (line[i])
	{
		update_quart_in(&is_in_quart[QUART_S], &is_in_quart[QUART_D], line[i]);
		if (!(ft_isalnum(line[i + 1]) || line[i + 1] == '_'
				|| line[i + 1] == '?'))
			i++;
		else if (line[i] == '$' && !is_in_quart[QUART_D])
		{
			after_var = wrap_malloc(expand_var(&line[i], exit_code, envp));
			*(ft_strchr(line, '$')) = '\0';
			line = wrap_malloc(ft_strjoin_free(line, after_var));
			i = 0;
		}
		else
			i++;
	}
	return (line);
}

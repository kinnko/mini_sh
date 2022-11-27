/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:16:28 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/23 12:41:47 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

void	exclude_lead(char *str)
{
	while (*str != '\0')
	{
		*str = *(str + 1);
		str++;
	}
}

bool	is_ignore(char *str, bool is_in_q[2])
{
	return ((*str == '"' && !is_in_q[QUART_S]) || (*str == '\''
			&& !is_in_q[QUART_D]));
}

t_strs	exclude_quote(t_strs args)
{
	size_t	i;
	bool	is_in_q[2];
	char	*arg;

	i = 0;
	reset_is_in_quart(is_in_q);
	while (args[i] != NULL)
	{
		arg = args[i];
		if (is_redirect(arg) && !is_in_q[QUART_S] && !is_in_q[QUART_D])
		{
			i += 2;
			continue ;
		}
		while (*arg != '\0')
		{
			update_quart_in(&(is_in_q[QUART_D]), &(is_in_q[QUART_S]), *arg);
			if (is_ignore(arg, is_in_q))
				exclude_lead(arg);
			else
				arg++;
		}
		i++;
	}
	return (args);
}

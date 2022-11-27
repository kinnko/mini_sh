/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quart_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:57:42 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/22 22:07:30 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <stdbool.h>

bool	check_quart_syntax(char *line, int *exit_code)
{
	bool	is_in_q[2];

	reset_is_in_quart(is_in_q);
	while (*line != '\0')
	{
		update_quart_in(&(is_in_q[QUART_D]), &(is_in_q[QUART_S]), *line);
		line++;
	}
	if (is_in_q[QUART_D])
	{
		ft_putstr_fd("minishell: syntax error: double quote not closed\n", 2);
		*exit_code = 258;
		return (false);
	}
	if (is_in_q[QUART_S])
	{
		ft_putstr_fd("minishell: syntax error: single quote not closed\n", 2);
		*exit_code = 258;
		return (false);
	}
	return (true);
}

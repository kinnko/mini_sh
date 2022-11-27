/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judge_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainoue <ainoue.@student.42tokyo.f>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 04:56:01 by ainoue            #+#    #+#             */
/*   Updated: 2022/10/23 04:58:33 by ainoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	is_redirect_add(char *str)
{
	return (str[0] == '>' && str[1] == '>');
}

bool	is_redirect_to(char *str)
{
	return (str[0] == '>');
}

bool	is_redirect_from(char *str)
{
	return (str[0] == '<');
}

bool	is_start_pipe(char *str)
{
	return (str[0] == '|');
}

bool	is_here_docs(char *str)
{
	return (str[0] == '<' && str[1] == '<');
}

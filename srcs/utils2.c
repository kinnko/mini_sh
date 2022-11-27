/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:40:07 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/22 22:07:30 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_strlen_to_c(char *args, char c)
{
	int	i;
	int	len;

	len = ft_strlen(args);
	i = -1;
	while (++i < len)
	{
		if (args[i] == c)
			return (i);
	}
	return (-1);
}

void	update_quart_in(bool *is_in_d_quart, bool *is_in_s_quart, char c)
{
	if (c == '"' && !(*is_in_s_quart))
		*is_in_d_quart = !(*is_in_d_quart);
	if (c == '\'' && !(*is_in_d_quart))
		*is_in_s_quart = !(*is_in_s_quart);
}

// must null check
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (ret);
}

bool	is_cmd(char *exec_path)
{
	if (exec_path == NULL)
		return (false);
	return (ft_strchr(exec_path, '/') == NULL);
}

void	reset_is_in_quart(bool is_in_q[2])
{
	is_in_q[QUART_S] = false;
	is_in_q[QUART_D] = false;
}

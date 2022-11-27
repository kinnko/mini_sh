/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:11:48 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/22 09:15:44 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

size_t	get_envp_count(t_strs envp)
{
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

t_true	put_envp(t_strs envp)
{
	size_t	i;

	i = -1;
	while (envp[++i] != NULL)
		printf("declare -x %s\n", envp[i]);
	return (true);
}

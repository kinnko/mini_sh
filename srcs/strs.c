/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:31:17 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/19 22:11:02 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	put_strs(t_strs strs)
{
	while (*strs != NULL)
	{
		printf("\"%s(%p)\"\n", *strs, strs);
		strs++;
	}
	printf("\"%s(%p)\"\n", *strs, strs);
	printf("\n");
}

void	remove_strs(t_strs strs, int index)
{
	free(strs[index]);
	while (strs[index] != NULL)
	{
		strs[index] = strs[index + 1];
		index++;
	}
}

size_t	length_strs(t_strs strs)
{
	size_t	size;

	size = 0;
	while (strs[size] != NULL)
		size++;
	return (size);
}

void	free_strs(t_strs strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:27:46 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/23 12:30:15 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

t_strs	create_new_envp(t_strs envp, char *add_env, ssize_t update_index)
{
	t_strs	new_envp;
	size_t	env_count;
	ssize_t	i;

	i = 0;
	env_count = get_envp_count(envp);
	new_envp = malloc(sizeof(char *) * (env_count + (update_index < 0) + 1));
	check_malloc_strs(new_envp);
	while (envp[i] != NULL)
	{
		if (i == update_index)
			new_envp[i] = wrap_malloc(ft_strdup(add_env));
		else
			new_envp[i] = wrap_malloc(ft_strdup(envp[i]));
		i++;
	}
	if (update_index == -1)
	{
		new_envp[i] = wrap_malloc(ft_strdup(add_env));
		++i;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

t_strs	clone_envp(t_strs envp)
{
	t_strs	new_envp;
	size_t	i;

	i = 0;
	new_envp = malloc(sizeof(char *) * (get_envp_count(envp) + 1));
	check_malloc_strs(new_envp);
	while (envp[i] != NULL)
	{
		new_envp[i] = wrap_malloc(ft_strdup(envp[i]));
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

t_strs	add_envp_value(t_strs envp, char *env_key, char *add_text)
{
	t_strs	new_envp;
	size_t	i;
	char	*envp_key;

	i = 0;
	new_envp = malloc(sizeof(char *) * (get_envp_count(envp) + 1));
	check_malloc_strs(new_envp);
	while (envp[i] != NULL)
	{
		envp_key = wrap_malloc(get_key(envp[i]));
		if (strequ(envp_key, env_key))
			new_envp[i] = wrap_malloc(ft_strjoin(envp[i], add_text));
		else
			new_envp[i] = wrap_malloc(ft_strdup(envp[i]));
		i++;
		free(envp_key);
	}
	new_envp[i] = NULL;
	return (new_envp);
}

t_strs	add_envp_key(t_strs envp, char *add_text)
{
	t_strs	new_envp;
	size_t	i;

	i = 0;
	new_envp = malloc(sizeof(char *) * (get_envp_count(envp) + 2));
	check_malloc_strs(new_envp);
	while (envp[i] != NULL)
	{
		new_envp[i] = wrap_malloc(ft_strdup(envp[i]));
		i++;
	}
	new_envp[i] = wrap_malloc(ft_strdup(add_text));
	i++;
	new_envp[i] = NULL;
	return (new_envp);
}

t_strs	overwrite_envp_value(t_strs envp, char *env_key, char *value)
{
	t_strs	new_envp;
	size_t	i;
	char	*envp_key;
	char	*buf;

	i = 0;
	new_envp = malloc(sizeof(char *) * (get_envp_count(envp) + 1));
	check_malloc_strs(new_envp);
	while (envp[i] != NULL)
	{
		envp_key = wrap_malloc(get_key(envp[i]));
		if (strequ(envp_key, env_key))
		{
			buf = wrap_malloc(ft_strjoin(env_key, "="));
			new_envp[i] = wrap_malloc(ft_strjoin(buf, value));
			free(buf);
		}
		else
			new_envp[i] = wrap_malloc(ft_strdup(envp[i]));
		i++;
		free(envp_key);
	}
	new_envp[i] = NULL;
	return (new_envp);
}

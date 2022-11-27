/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:30:13 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/22 23:24:37 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static char	*get_home_path(t_strs envp)
{
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "HOME=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

static char	*expand_home_dir(char *path, t_strs envp)
{
	char	*tmp;

	if (path == NULL)
		return (NULL);
	tmp = ft_strjoin(get_home_path(envp), path + 1);
	if (tmp == NULL)
		return (NULL);
	path = tmp;
	return (path);
}

int	do_cd_cmd(t_strs args, t_shell *shell)
{
	char	*path;
	char	*home_path;
	t_strs	*envp;

	envp = &(shell->envp);
	home_path = NULL;
	if (!(length_strs(args) <= 2))
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (false);
	}
	path = args[1];
	if (path == NULL)
		return (cd_absolute_path(get_home_path(*envp), shell) == false);
	if (path[0] == '~')
	{
		home_path = expand_home_dir(path, *envp);
		cd_absolute_path(home_path, shell);
		free(home_path);
		return (true);
	}
	else
		cd_absolute_path(path, shell);
	return (true);
}

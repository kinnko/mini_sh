/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_absolute_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 23:24:54 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/23 17:00:01 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	set_pwd(char *pwd, t_strs *envp)
{
	size_t	i;
	char	*envp_key;
	t_strs	tmp;
	char	*text;

	i = 0;
	while ((*envp)[i] != NULL)
	{
		envp_key = wrap_malloc(get_key((*envp)[i]));
		if (strequ(envp_key, "PWD"))
		{
			tmp = overwrite_envp_value(*envp, "PWD", pwd);
			free_strs(*envp);
			free(envp_key);
			*envp = tmp;
			return ;
		}
		free(envp_key);
		i++;
	}
	text = wrap_malloc(ft_strjoin("PWD=", pwd));
	tmp = add_envp_key(*envp, text);
	free_strs(*envp);
	*envp = tmp;
	free(text);
}

static void	set_old_pwd(char *old_pwd, t_strs *envp)
{
	size_t	i;
	char	*envp_key;
	t_strs	tmp;
	char	*text;

	i = 0;
	while ((*envp)[i] != NULL)
	{
		envp_key = wrap_malloc(get_key((*envp)[i]));
		if (strequ(envp_key, "OLDPWD"))
		{
			tmp = overwrite_envp_value(*envp, "OLDPWD", old_pwd);
			free_strs(*envp);
			free(envp_key);
			*envp = tmp;
			return ;
		}
		free(envp_key);
		i++;
	}
	text = wrap_malloc(ft_strjoin("OLDPWD=", old_pwd));
	tmp = add_envp_key(*envp, text);
	free_strs(*envp);
	*envp = tmp;
	free(text);
}

bool	cd_absolute_path(char *to_path, t_shell *shell)
{
	char	*cwd_buf;
	t_strs	*envp;

	envp = &(shell->envp);
	cwd_buf = getcwd((char *) NULL, 0);
	if (cwd_buf == NULL)
	{
		perror("minishell: getcwd");
		return (false);
	}
	if (chdir(to_path) == 0)
	{
		set_old_pwd(cwd_buf, envp);
		free(cwd_buf);
		cwd_buf = wrap_malloc(getcwd((char *) NULL, 0));
		set_pwd(cwd_buf, envp);
		update_current_dir(shell, cwd_buf);
		return (true);
	}
	free(cwd_buf);
	if (strequ(to_path, ""))
		return (true);
	ft_putstr_fd("minishell: ", 2);
	perror(to_path);
	return (false);
}

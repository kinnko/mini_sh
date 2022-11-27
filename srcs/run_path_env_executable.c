/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_path_env_executable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:31:14 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/22 08:24:04 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	**get_path_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (ft_strlen(envp[i]) >= 5 && ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(&(envp[i][5]), ':'));
	}
	return (NULL);
}

int	put_cmd_not_found(char *cmd_name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (127);
}

// This function doesn't return when successful.
void	file_exec(const char *exec_file, char *const args[], t_strs envp)
{
	int	exit_code;

	exit_code = execve(exec_file, args, envp);
	if (exit_code == -1)
		perror(exec_file);
}

int	run_path_env_executable_core(char **env_path_list, char *exec_file,
		char **args, t_strs envp)
{
	size_t	i;
	char	*file_path;
	int		exit_code;

	i = 0;
	while (env_path_list[i] != NULL)
	{
		file_path = path_concat(env_path_list[i], exec_file);
		if (file_path == NULL)
			return (STATUS_FAILS);
		if (exist_file(file_path))
		{
			file_exec(file_path, args, envp);
			free(file_path);
			break ;
		}
		free(file_path);
		i++;
	}
	exit_code = put_cmd_not_found(exec_file);
	return (exit_code);
}

int	run_path_env_executable(char *exec_file, char **args, t_strs envp)
{
	t_strs	env_path_list;
	int		exit_code;

	env_path_list = get_path_env(envp);
	if (env_path_list == NULL)
		return (put_cmd_not_found(exec_file));
	exit_code = run_path_env_executable_core(env_path_list, exec_file, args,
			envp);
	free_strs(env_path_list);
	return (exit_code);
}

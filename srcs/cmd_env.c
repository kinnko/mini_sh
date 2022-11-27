/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:30:20 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/22 08:25:19 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

static int	print_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
	{
		if (ft_strchr(env[i], '=') != NULL)
			printf("%s\n", env[i]);
	}
	return (STATUS_SUCCESS);
}

void	print_and_check_args_env(char **args, t_shell *shell)
{
	int		i;
	char	**new_envp;
	char	**old_envp;

	i = -1;
	while (shell->envp[++i] != NULL)
		if (ft_strncmp(args[1], shell->envp[i], ft_strlen_to_c(args[1],
					'=')) == 0)
			break ;
	if (shell->envp[i] == NULL)
		i = -1;
	new_envp = create_new_envp(shell->envp, args[1], i);
	old_envp = shell->envp;
	shell->envp = new_envp;
	shell->exit_code = 0;
	if (args[2] == NULL)
		print_env(new_envp);
	else
		execute(&(args[2]), shell);
	shell->envp = old_envp;
	free_strs(new_envp);
}

int	do_env_cmd(char **args, t_shell *shell)
{
	if (args[1] == NULL)
		return (print_env(shell->envp));
	else if (ft_strchr(args[1], '=') == NULL)
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		return (127);
	}
	print_and_check_args_env(args, shell);
	return (shell->exit_code);
}

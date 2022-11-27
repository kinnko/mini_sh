/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:30:37 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/23 16:52:08 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

int		ft_strlen_to_c(char *args, char c);

void	unset_err(char *args)
{
	ft_putstr_fd("unset: ", 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd(" : not a valid identifier\n", 2);
}

char	**delete_env(char **env, int line_to_update)
{
	char	**new;
	int		line;
	int		i;
	int		j;

	line = 0;
	j = 0;
	while (env[line] != NULL)
		++line;
	new = malloc(sizeof(char *) * line);
	i = -1;
	while (env[++i] != NULL)
	{
		if (i == line_to_update)
			++j;
		else
			new[i - j] = ft_strdup(env[i]);
	}
	new[i - j] = NULL;
	return (new);
}

void	exe_unset(char **args, t_shell *shell)
{
	char	**new;
	int		i;
	int		j;

	i = -1;
	while (shell->envp[++i] != NULL)
	{
		j = ft_strlen(args[1]);
		if (ft_strncmp(args[1], shell->envp[i], j) == 0
			&& (shell->envp[i][j] == '=' || shell->envp[i][j] == '\0'))
			break ;
	}
	if (shell->envp[i] != NULL)
	{
		new = delete_env(shell->envp, i);
		free_strs(shell->envp);
		shell->envp = new;
	}
}

bool	do_unset_cmd(char **args, t_shell *shell)
{
	int	i;
	int	j;

	j = 0;
	while (args[++j] != NULL)
	{
		i = -1;
		while (args[j][++i] != '\0')
			if (ft_isalnum((int)args[j][i]) == 0 && !(args[j][i] == '_'))
				break ;
		if (args[j][i] != '\0' || ft_isdigit((int)args[j][0]))
			unset_err(args[j]);
		else
			exe_unset(args, shell);
	}
	return (true);
}

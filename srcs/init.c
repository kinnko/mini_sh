/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:30:58 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/23 15:59:58 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stddef.h>
#include <stdlib.h>

char	**init_envp(char **envp)
{
	char	**res;
	int		line;

	line = 0;
	while (envp[line] == NULL)
		++line;
	res = clone_envp(envp);
	return (res);
}

void	set_builtin_cmd_list(t_shell *shell)
{
	size_t	i;

	i = 0;
	shell->builtin_list = check_malloc_strs(malloc(sizeof(char *)
				* BUILTIN_CMD_COUNT));
	shell->builtin_list[i++] = "echo";
	shell->builtin_list[i++] = "cd";
	shell->builtin_list[i++] = "pwd";
	shell->builtin_list[i++] = "export";
	shell->builtin_list[i++] = "unset";
	shell->builtin_list[i++] = "env";
	shell->builtin_list[i++] = "exit";
}

void	set_redirect(t_redirect *redirect)
{
	redirect->std_in = dup(STDIN);
	redirect->std_out = dup(STDOUT);
}

void	update_current_dir(t_shell *shell, char *new)
{
	free(shell->current_dir);
	shell->current_dir = new;
}

void	init_shell(t_shell *shell, char *envp[])
{
	set_builtin_cmd_list(shell);
	set_redirect(&shell->redirect);
	shell->envp = init_envp(envp);
	shell->exit_code = 0;
	shell->current_dir = getcwd((char *) NULL, 0);
	return ;
}

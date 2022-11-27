/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:30:41 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/22 08:30:52 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	run_builtin_cmd(t_strs args, t_shell *shell)
{
	if (strequ(args[0], "echo"))
		shell->exit_code = do_echo_cmd(args);
	else if (strequ(args[0], "cd"))
		shell->exit_code = do_cd_cmd(args, shell);
	else if (strequ(args[0], "pwd"))
		shell->exit_code = !do_pwd_cmd(shell);
	else if (strequ(args[0], "export"))
		shell->exit_code = !do_export_cmd(args, shell);
	else if (strequ(args[0], "unset"))
		shell->exit_code = !do_unset_cmd(args, shell);
	else if (strequ(args[0], "env"))
		shell->exit_code = do_env_cmd(args, shell);
	else if (strequ(args[0], "exit"))
		shell->exit_code = do_exit_cmd(args, shell->exit_code);
	else
		exit(STATUS_FAILS);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:30:27 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/23 12:30:15 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

bool	check_valid_args_plus(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i] != '=')
		if (ft_isalnum((int)arg[i]) == 0 && !(arg[i] == '_'))
			break ;
	if ((arg[i] != '=' && !(arg[i] == '+' && arg[i + 1] == '='))
		|| ft_isdigit((int)arg[0]) || arg[0] == '=')
		return (export_error(arg));
	return (true);
}

bool	check_valid_args(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i] != '\0')
		if (ft_isalnum((int)arg[i]) == 0 && !(arg[i] == '_'))
			break ;
	if (arg[i] != '\0' || ft_isdigit((int)arg[0]))
		return (export_error(arg));
	return (true);
}

bool	is_add_value(char *key_value)
{
	while (key_value[1] != '\0')
	{
		if (key_value[0] == '=')
			return (false);
		if (key_value[0] == '+' && key_value[1] == '=')
			return (true);
		key_value++;
	}
	return (false);
}

void	assignment_process(char *arg, t_shell *shell)
{
	char	**new;
	char	*key;
	char	*value;

	key = wrap_malloc(get_key(arg));
	value = wrap_malloc(get_value(arg));
	if (is_add_value(arg))
	{
		if (has_key(shell->envp, key))
			new = add_envp_value(shell->envp, key, value);
		else
			new = add_envp_key(shell->envp, arg);
	}
	else
	{
		if (has_key(shell->envp, key))
			new = overwrite_envp_value(shell->envp, key, value);
		else
			new = add_envp_key(shell->envp, arg);
	}
	free_strs(shell->envp);
	shell->envp = check_malloc_strs(new);
	free(key);
	free(value);
}

bool	do_export_cmd(char **args, t_shell *shell)
{
	t_strs	new;

	if (args[1] == NULL)
		return (put_envp(shell->envp));
	args++;
	while (*args != NULL)
	{
		if (ft_strchr(*args, '=') == NULL)
		{
			if (!check_valid_args(*args))
				return (false);
			if (has_key(shell->envp, *args))
			{
				args++;
				continue ;
			}
			new = add_envp_key(shell->envp, *args);
			free_strs(shell->envp);
			shell->envp = new;
		}
		else if (check_valid_args_plus(*args))
			assignment_process(*args, shell);
		args++;
	}
	return (true);
}

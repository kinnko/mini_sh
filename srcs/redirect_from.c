/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_from.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:31:06 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/18 08:49:31 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "minishell.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

bool	redirect_from_error(char *filename)
{
	if (write(2, "minishell: ", ft_strlen("minishell: ")) == -1)
		put_error_exit();
	perror(filename);
	return (false);
}

bool	redirect_from(char *from_path)
{
	int	fd;

	fd = open(from_path, O_RDONLY);
	if (fd == -1)
		return (redirect_from_error(from_path));
	if (dup2(fd, STDIN) == -1)
		return (redirect_from_error(from_path));
	close(fd);
	return (true);
}

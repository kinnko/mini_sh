/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_add_to.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:31:05 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/21 00:06:57 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

bool	put_file_text_error(void)
{
	if (ft_putstr_fd("minishell: ", 2) == -1)
		perror("minishell");
	else
		perror("put_file_text");
	return (false);
}

// fd must be opened
bool	put_file_text(int fd)
{
	char	buf[1024];
	int		read_size;
	int		buf_fd;

	buf_fd = open("/tmp/minishell_buf", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (buf_fd == -1)
		return (put_file_text_error());
	read_size = read(fd, buf, 1024);
	while (read_size > 0)
	{
		if (write(buf_fd, buf, read_size) == -1)
			return (put_file_text_error());
	}
	read_size = read(buf_fd, buf, 1024);
	while (read_size > 0)
		ft_putstr_fd(buf, 1);
	close(buf_fd);
	return (true);
}

bool	put_redirect_add_to_error(char *filename)
{
	if (ft_putstr_fd("minishell: ", 2) == -1)
		perror("minishell");
	else
		perror(filename);
	return (false);
}

bool	redirect_add_to(char *add_to_path)
{
	int	fd;

	fd = open(add_to_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (put_redirect_add_to_error(add_to_path));
	if (dup2(fd, STDOUT) == -1)
		return (put_redirect_add_to_error(add_to_path));
	put_file_text(fd);
	close(fd);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yueyama@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:43:10 by yueyama           #+#    #+#             */
/*   Updated: 2022/04/18 18:24:30 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putstr_fd(char *s, int fd)
{
	size_t	len;
	ssize_t	total;

	if (s == NULL)
		return (-1);
	len = ft_strlen(s);
	total = write(fd, s, len);
	if (total == -1)
		total = 0;
	return ((size_t)total);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yueyama@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:51:35 by yueyama           #+#    #+#             */
/*   Updated: 2022/04/17 23:07:45 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_putnbr_fd(int n, int fd)
{
	unsigned int	base;
	unsigned int	u_n;
	unsigned int	n_digit;
	size_t			total;

	base = 10;
	u_n = n;
	total = 0;
	if (n < 0)
	{
		u_n = ~n + 1;
		total += ft_putchar_fd('-', fd);
	}
	n_digit = 1;
	while (u_n / n_digit >= base)
	{
		n_digit *= base;
	}
	while (n_digit > 0)
	{
		total += ft_putchar_fd(u_n / n_digit + '0', fd);
		u_n %= n_digit;
		n_digit /= base;
	}
	return (total);
}

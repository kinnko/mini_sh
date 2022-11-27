/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yueyama@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 20:09:36 by yueyama           #+#    #+#             */
/*   Updated: 2022/02/01 18:50:19 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	malloc_byte(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		size++;
	while (n)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*str_num;
	int		is_minus;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	str_num = (char *)malloc(sizeof(char) * (malloc_byte(n) + 1));
	if (str_num == NULL)
		return (NULL);
	str_num[malloc_byte(n)] = '\0';
	is_minus = (n < 0);
	if (is_minus)
		n = (-n);
	while (n > 0)
	{
		str_num[malloc_byte(n) - 1 + is_minus] = n % 10 + '0';
		n /= 10;
	}
	if (is_minus)
		str_num[malloc_byte(n) - 1] = '-';
	return (str_num);
}

// #include <limits.h>

// int	main(void)
// {
// 	printf("%s\n", ft_itoa(INT_MAX));
// 	printf("%s\n", ft_itoa(INT_MIN));
// 	printf("%s\n", ft_itoa(0));
// 	for (int i = -10; i < 10; i++)
// 	{
// 		printf("%s\n", ft_itoa(i));
// 	}
// }

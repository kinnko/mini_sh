/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yueyama@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:30:47 by yueyama           #+#    #+#             */
/*   Updated: 2022/01/30 19:01:28 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t size)
{
	unsigned char	*uc_str1;
	unsigned char	*uc_str2;

	uc_str1 = (unsigned char *)str1;
	uc_str2 = (unsigned char *)str2;
	while (size != 0)
	{
		if (*uc_str1 != *uc_str2)
			return (*uc_str1 - *uc_str2);
		uc_str1++;
		uc_str2++;
		size--;
	}
	return (0);
}

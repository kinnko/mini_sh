/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yueyama@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:24:59 by yueyama           #+#    #+#             */
/*   Updated: 2022/01/30 19:01:06 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int c, size_t size)
{
	unsigned char	*uc_ptr;

	uc_ptr = (unsigned char *)ptr;
	while (size != 0)
	{
		if (*uc_ptr == (unsigned char)c)
			return ((void *)uc_ptr);
		uc_ptr++;
		size--;
	}
	return (NULL);
}

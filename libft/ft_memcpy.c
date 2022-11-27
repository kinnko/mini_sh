/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yueyama@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:03:19 by yueyama           #+#    #+#             */
/*   Updated: 2022/02/01 18:23:05 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dest_p;
	char	*src_p;

	if (dest == src)
		return (dest);
	dest_p = (char *)dest;
	src_p = (char *)src;
	while (n != 0)
	{
		*dest_p++ = *src_p++;
		n--;
	}
	return (dest);
}

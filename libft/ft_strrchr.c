/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yueyama@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:15:44 by yueyama           #+#    #+#             */
/*   Updated: 2022/01/29 20:37:55 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*rtn_ptr;

	rtn_ptr = NULL;
	while (1)
	{
		if (*s == (char)c)
			rtn_ptr = (char *)s;
		if (*s == '\0')
			break ;
		s++;
	}
	return (rtn_ptr);
}

// int	main(void){
// 	printf("%d\n",*ft_strrchr("test",0) == '\0');
// }

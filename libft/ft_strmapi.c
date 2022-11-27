/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yueyama@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:59:23 by yueyama           #+#    #+#             */
/*   Updated: 2022/02/01 19:01:47 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	char			*mapped_str;
	unsigned int	i_str;

	if (str == NULL || f == NULL)
		return (NULL);
	mapped_str = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (mapped_str == NULL)
		return (NULL);
	i_str = 0;
	while (str[i_str] != '\0')
	{
		mapped_str[i_str] = (*f)(i_str, str[i_str]);
		i_str++;
	}
	mapped_str[i_str] = '\0';
	return (mapped_str);
}

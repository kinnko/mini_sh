/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yueyama@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:35:28 by yueyama           #+#    #+#             */
/*   Updated: 2022/01/30 19:44:37 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i_s;

	if (s == NULL || f == NULL)
		return ;
	i_s = 0;
	while (s[i_s] != '\0')
	{
		(*f)(i_s, &s[i_s]);
		i_s++;
	}
}

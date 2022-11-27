/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yueyama@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:12:44 by yueyama           #+#    #+#             */
/*   Updated: 2022/02/01 18:50:24 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*rtn_str;

	if (str == NULL)
		return (NULL);
	if (ft_strlen(str) <= start || len == 0)
		return (ft_strdup(""));
	rtn_str = (char *)malloc((len + 1) * sizeof(char));
	if (rtn_str == NULL)
		return (NULL);
	ft_strlcpy(rtn_str, str + start, len + 1);
	return (rtn_str);
}

// int	main(void)
// {
// 	char *s = ft_substr("tripouille", 0, 42000);
// 	printf("%s\n", s);
// 	free(s);
// }

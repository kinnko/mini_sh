/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yueyama@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:28:35 by yueyama           #+#    #+#             */
/*   Updated: 2022/01/31 21:25:02 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	contains(const char *chars, char c)
{
	while (*chars)
	{
		if (*chars == c)
			return (1);
		chars++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*rtn_str;
	size_t	end_i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1 != '\0' && contains(set, *s1))
		s1++;
	if (*s1 == '\0')
		return (ft_strdup(""));
	end_i = ft_strlen(s1) - 1;
	while (end_i != 0 && contains(set, s1[end_i]))
		end_i--;
	rtn_str = ft_substr((char *)s1, 0, end_i + 1);
	return (rtn_str);
}

// #include <stdio.h>
// #include <string.h>

// void	check_strtrim(char *s1, char *set, char *expect_str)
// {
// 	char	*rtn_str;

// 	rtn_str = ft_strtrim(s1, set);
// 	printf("%s\n", rtn_str);
// 	if (rtn_str == NULL)
// 		printf("rtn_str is NULL\n");
// 	if (rtn_str != NULL && strcmp(rtn_str, expect_str) != 0)
// 		printf("rtn_str is not expected\n");
// 	free(rtn_str);
// }

// void	test_strtrim(void)
// {
// 	check_strtrim(" 1test1 11 ", "1 ", "test");
// 	check_strtrim("   ", "\n\t ", "");
// }

// int	main(void)
// {
// 	test_strtrim();
// }

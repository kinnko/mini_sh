/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yueyama@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:53:51 by yueyama           #+#    #+#             */
/*   Updated: 2022/01/31 21:28:36 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	strclen(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

static size_t	count_el(char *str, char c)
{
	size_t	split_count;
	size_t	i;

	if (ft_strlen(str) == 0)
		return (0 + 1);
	i = 0;
	split_count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c && str[i + 1] != c && str[i + 1] != '\0')
			split_count++;
		i++;
	}
	if (str[0] == c)
		split_count--;
	return (split_count + 1 + 1);
}

static void	free_all(char **str_array, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(str_array[i]);
		i++;
	}
	free(str_array);
}

static char	**generate_split_strs(char **split_strs, char const *str, char c)
{
	size_t	i;

	i = 0;
	while (1)
	{
		while (*str == c && c != '\0')
			str++;
		if (*str == '\0')
		{
			split_strs[i] = NULL;
			return (split_strs);
		}
		split_strs[i] = ft_substr(str, 0, strclen((char *)str, c));
		if (split_strs[i] == NULL)
		{
			free_all(split_strs, i);
			return (NULL);
		}
		str += strclen((char *)str, c);
		i++;
	}
}

char	**ft_split(char const *str, char c)
{
	char	**split_strs;

	if (str == NULL)
		return (NULL);
	split_strs = (char **)malloc(sizeof(char *) * count_el((char *)str, c));
	if (split_strs == NULL)
		return (NULL);
	return (generate_split_strs(split_strs, str, c));
}

// int	main(void)
// {
// 	printf("%d\n", count_el("a", 'a') /* == 0 + 1 */);
// 	printf("%d\n", count_el("aba", 'b') /* == 2 + 1 */);
// 	printf("%d\n", count_el("abba", 'b') /* == 2 + 1 */);
// 	printf("%d\n", count_el("ba", 'a') /* == 1 + 1 */);
// 	printf("%d\n", count_el("ab", 'a') /* == 1 + 1 */);
// 	printf("%d\n", count_el("aba", 'a') /* == 1 + 1 */);
// 	printf("%d\n", count_el("", 'a') /* == 0 + 1 */);
// 	printf("%d\n", count_el("fldkashfdsa", '\0') /* == 1 + 1 */);
// }

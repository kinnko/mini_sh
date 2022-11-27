/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yueyama@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 05:46:00 by yueyama           #+#    #+#             */
/*   Updated: 2022/01/29 20:37:02 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*mapped_list;

	if (lst == NULL || f == NULL)
		return (NULL);
	mapped_list = NULL;
	while (lst != NULL)
	{
		new_node = ft_lstnew((*f)(lst->content));
		if (new_node == NULL)
		{
			ft_lstclear(&mapped_list, del);
			return (NULL);
		}
		ft_lstadd_back(&mapped_list, new_node);
		lst = lst->next;
	}
	return (mapped_list);
}
/*

void	*func(void *content)
{
	return (strdup("OK !"));
}

int	main(void)
{
	t_list *l = ft_lstnew(strdup(" 1 2 3 "));
	t_list	*ret;

	l->next = ft_lstnew(strdup("ss"));
	l->next->next = ft_lstnew(strdup("-_-"));
	ret = ft_lstmap(l, func, ((void *)0));
	if (!strcmp(ret->content, "OK !") && !strcmp(ret->next->content, "OK !") &&
		!strcmp(ret->next->next->content, "OK !") &&
		!strcmp(l->content, " 1 2 3 ") && !strcmp(l->next->content, "ss") &&
		!strcmp(l->next->next->content, "-_-"))
		puts("ok");
	puts("no");
}
 */

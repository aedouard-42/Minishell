/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:52:44 by aedouard          #+#    #+#             */
/*   Updated: 2021/05/26 12:17:03 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	begin = ft_lstnew(f(lst->content));
	if (!begin)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
		{
			ft_lstclear(&begin, del);
			return (begin);
		}
		ft_lstadd_back(&begin, tmp);
		lst = lst->next;
	}
	return (begin);
}

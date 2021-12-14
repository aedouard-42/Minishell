/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <aedouard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 21:12:59 by aedouard          #+#    #+#             */
/*   Updated: 2021/05/26 12:21:43 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	int		size;
	t_list	*list;

	size = sizeof(t_list);
	list = malloc(size);
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

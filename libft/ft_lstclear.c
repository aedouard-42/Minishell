/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:25:46 by aedouard          #+#    #+#             */
/*   Updated: 2021/05/26 12:06:31 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cl;
	t_list	*next_tmp;

	cl = *lst;
	while (cl)
	{
		next_tmp = cl->next;
		ft_lstdelone(cl, del);
		cl = next_tmp;
	}
	*lst = NULL;
}

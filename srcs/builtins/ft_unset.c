/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:54:47 by aedouard          #+#    #+#             */
/*   Updated: 2021/11/09 10:54:49 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_delete_relink(t_list *list, t_list* prev, t_list *cur)
{
	if (cur == list)
	{
		list = cur->next;
		ft_lstdelone(cur, &ft_free_content);
	}
	else
	{
		prev->next = cur->next;
		ft_lstdelone(cur, &ft_free_content);
	}
}

void	remove_from_list(char *str, t_list *list)
{
	t_list *prev;
	t_list *cur;

	cur = list;
	prev = NULL;
	while(cur)
	{
		if (found_in_env(str, cur->content))
			ft_delete_relink(list, prev, cur);
		prev = cur;
		cur = cur->next;
	}
}

void	builtin_unset(t_list *lst, char **strs)
{
	int i;

	i = 0;
	while (strs[i])
	{
		remove_from_list(strs[i], lst);
		i++;
	}
}
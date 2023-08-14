/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:54:47 by aedouard          #+#    #+#             */
/*   Updated: 2022/01/11 14:12:43 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_relink(t_list **list, t_list *prev, t_list *cur)
{
	t_list	*tmp;

	tmp = NULL;
	if (cur == *list)
	{
		tmp = *list;
		*list = cur->next;
		ft_lstdelone(tmp, &ft_free_content);
	}
	else
	{
		prev->next = cur->next;
		ft_lstdelone(cur, &ft_free_content);
	}
}

void	remove_from_list(char *str, t_list **list)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*tmp;

	cur = *list;
	prev = NULL;
	while (cur)
	{
		tmp = cur->next;
		if (found_in_env(str, cur->content))
			ft_delete_relink(list, prev, cur);
		prev = cur;
		cur = tmp;
	}
}

int	check_unset_validity(char *str)
{
	int	i;
	int	found_alpha;

	i = 0;
	found_alpha = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		if (ft_isalpha(str[i]))
			found_alpha = 1;
		if (found_alpha == 0)
		{
			if (!ft_isalpha(str[i] && str[i] != '_'))
				return (0);
		}
		i++;
	}
	return (1);
}

void	builtin_unset(t_list **lst, char **strs)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	if (!strs || !strs[i])
		return ;
	while (strs[i])
	{
		if (!check_unset_validity(strs[i]))
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd(strs[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		remove_from_list(strs[i], lst);
		i++;
	}
	g_exit_status = status;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:47:44 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/10 15:50:34 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(void *content)
{
	t_env_str	*content2;

	content2 = (t_env_str *)content;
	if ((content2->value != NULL) && content2->value[0] != '\0')
		printf("%s=%s\n", content2->name, content2->value);
	else
		printf("%s\n", content2->name);
}

int	check_export_validity(char *str)
{
	int	i;
	int	found_alpha;

	i = 0;
	found_alpha = 0;
	if (!str || !str[0] || str[0] == '=')
		return (-1);
	while (str[i] && str[i] != '=')
	{
		if (ft_isalpha(str[i]) == 1)
			found_alpha = 1;
		else
		{
			if (ft_isdigit(str[i]) && !found_alpha)
				return (-1);
			else if (!ft_isdigit(str[i]) && str[i] != '_')
				return (-1);
		}
		i++;
	}
	if (str[i] != '=')
		return (0);
	return (1);
}

int	compare_data(t_list *a, t_list *b)
{
	t_env_str	*env_a;
	t_env_str	*env_b;
	int			len_a;
	int			len_b;

	env_a = (t_env_str *)a->content;
	env_b = (t_env_str *)b->content;
	len_a = ft_strlen(env_a->name);
	len_b = ft_strlen(env_b->name);
	if (len_b < len_a)
		len_a = len_b;
	if (ft_strncmp (env_a->name, env_b->name, len_a) > 0)
		return (1);
	return (0);
}

void	lst_swap(t_list *a, t_list *b)
{
	t_env_str	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

void	ft_sort_export(t_list *lst)
{
	int		swap;
	t_list	*lsthead;

	lsthead = lst;
	swap = 1;
	while (swap)
	{
		swap = 0;
		while (lst->next)
		{
			if (compare_data(lst, lst->next))
			{
				lst_swap(lst, lst->next);
				swap = 1;
			}
			lst = lst->next;
		}
		lst = lsthead;
	}
}

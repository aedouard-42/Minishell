/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_lst_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:52:39 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/09 21:57:32 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_arg_nbr(t_tokenl *token)
{
	int			res;
	t_tokenl	*temp;

	res = 0;
	temp = token;
	while (temp)
	{
		if (temp->type == ARG)
			res++;
		else if (temp->type == PIPE)
			return (res);
		temp = temp->next;
	}
	return (res);
}

t_cmd	*ft_cmdget_last(t_cmd *first)
{
	t_cmd	*temp;

	temp = first;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	ft_cmd_free(void *data)
{
	int	i;

	i = 0;
	if ((t_cmd *)data)
	{
		if (((t_cmd *)data)->args)
		{
			while (((t_cmd *)data)->args[i])
			{
				free(((t_cmd *)data)->args[i]);
				((t_cmd *)data)->args[i] = NULL;
				i++;
			}
			free(((t_cmd *)data)->args);
			((t_cmd *)data)->args = NULL;
		}
		ft_redirall_free(&(((t_cmd *)data)->redir));
		free((t_cmd *)data);
	}
	return ;
}

void	ft_cmdall_free(t_cmd **first)
{
	t_cmd	*temp;

	while (*first)
	{
		temp = *first;
		*first = (*first)->next;
		ft_cmd_free(temp);
	}
	return ;
}

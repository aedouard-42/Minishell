/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tok_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:11:22 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/09 13:14:01 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_clear(t_tokenl *first)
{
	t_tokenl	*temp;
	t_tokenl	*temp2;

	temp = first;
	while (temp != NULL)
	{
		temp2 = temp;
		if (temp->str)
			free(temp->str);
		temp = temp->next;
		free(temp2);
	}
}

t_tokenl	*ft_toknew(void)
{
	t_tokenl	*ret;

	ret = malloc(sizeof(t_tokenl));
	if (ret == NULL)
		return (ret);
	ret->type = 7;
	ret->str = NULL;
	ret->next = NULL;
	ret->id = -1;
	return (ret);
}

t_tokenl	*ft_tokadd_back(t_tokenl **begin_list, t_tokenl *new)
{
	t_tokenl	*temp;

	temp = *begin_list;
	if (*begin_list == NULL)
	{
		*begin_list = new;
		(*begin_list)->id = 1;
		return (new);
	}
	while (temp->next != NULL)
		temp = temp->next;
	new->id = temp->id + 1;
	temp->next = new;
	return (new);
}

void	ft_tok_free(t_tokenl *token)
{
	if (token)
	{
		if ((token)->str != NULL)
		{
			free((token)->str);
			token->str = NULL;
		}
		free(token);
	}
	return ;
}

void	ft_tokall_free(t_tokenl **first)
{
	t_tokenl	*temp;

	while (*first)
	{
		temp = *first;
		*first = (*first)->next;
		ft_tok_free(temp);
	}
	return ;
}

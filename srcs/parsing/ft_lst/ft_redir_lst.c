/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:55:44 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/09 13:56:12 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	xft_strcmp(char *s1, char *s2)
{
	int	i;
	int	size[2];

	size[0] = ft_strlen(s1);
	size[1] = ft_strlen(s2);
	if (size[0] != size[1])
		return (0);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

void	ft_rediradd_back(t_redir **begin_list, t_redir *new)
{
	t_redir	*ptr;

	if (*begin_list == NULL)
		*begin_list = new;
	else
	{
		ptr = *begin_list;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = new;
	}
}

t_redir	*ft_redirnew(t_tokenl *token, t_cmd **first, t_list **env)
{
	t_redir	*res;

	res = malloc(sizeof(t_redir));
	if (res == NULL)
		exit_get_lst(first, token, env);
	if (xft_strcmp(token->str, "<") == 1)
		res->type = REDIR_IN;
	else if (xft_strcmp(token->str, "<<") == 1)
		res->type = REDIR_IN2;
	else if (xft_strcmp(token->str, ">") == 1)
		res->type = REDIR_OUT;
	else if (xft_strcmp(token->str, ">>") == 1)
		res->type = REDIR_OUT2;
	else
		res->type = -1;
	if (token->next)
		res->filename = ft_strdup(token->next->str);
	res->next = NULL;
	return (res);
}

void	ft_redir_free(t_redir *redir)
{
	if (redir)
	{
		if (redir->filename)
		{
			free(redir->filename);
			redir->filename = NULL;
		}
		free(redir);
	}
	return ;
}

void	ft_redirall_free(t_redir **first)
{
	t_redir	*temp;

	while (*first)
	{
		temp = *first;
		*first = (*first)->next;
		ft_redir_free(temp);
	}
	return ;
}

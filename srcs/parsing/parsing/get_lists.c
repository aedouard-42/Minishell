/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:56:51 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/09 13:56:52 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_tokenl *first)
{
	int			i;
	t_tokenl	*temp;

	temp = first;
	i = 1;
	while (temp)
	{
		if (temp->type == PIPE)
			i++;
		temp = temp->next;
	}
	return (i);
}

t_cmd	*get_cmd_lst(t_tokenl *first, t_list **lst_env)
{
	t_cmd		*ret;
	t_tokenl	*token;

	ret = NULL;
	token = first;
	while (token)
	{
		ft_cmdadd_back(&ret, ft_cmdnew(&ret, token, NULL, lst_env));
		while (token && token->type != PIPE)
		{
			if (token->type == REDIR)
				ft_rediradd_back(&(ft_cmdget_last(ret)->redir),
					ft_redirnew(token, &ret, lst_env));
			token = token->next;
		}
		if (token)
			token = token->next;
	}
	return (ret);
}

void	exit_get_lst(t_cmd **fst, t_tokenl *token, t_list **env)
{
	ft_cmdall_free(fst);
	ft_tokall_free(&token);
	ft_lstclear(env, *ft_free_content);
	ft_putstr_fd(ERROR_MALLOC, 2);
	exit(127);
}

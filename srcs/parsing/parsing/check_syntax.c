/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 07:11:37 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/10 17:25:55 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_syntax(t_tokenl *token)
{
	if (token->next == NULL)
	{
		ft_putstr_fd(WRONGL_PIPE, 1);
		return (0);
	}
	if (token->next->type == PIPE || ft_strlen(token->str) > 1)
	{
		ft_putstr_fd(MULTI_PIPE, 1);
		return (0);
	}
	return (1);
}

int	check_redir_syntax_help(t_tokenl *token, int i)
{
	if (token->str[i] != token->str[0] || ft_strlen(token->str) > 2)
	{
		ft_putstr_fd(MULTI_REDIR, 1);
		return (0);
	}
	return (1);
}

int	check_redir_syntax(t_tokenl *token)
{
	int	i;

	if (token->next == NULL)
	{
		ft_putstr_fd(WRONG_REDIR, 1);
		return (0);
	}
	if (token->next->type != FILE || token->next->str == NULL)
	{
		ft_putstr_fd(WRONG_REDIR, 1);
		return (0);
	}
	i = 0;
	while (token->str[i])
	{
		if (check_redir_syntax_help(token, i) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_syntax_error(t_tokenl *first)
{
	t_tokenl	*temp;
	int			ret;

	ret = 1;
	if (first->type == PIPE)
	{
		ft_putstr_fd(WRONGF_PIPE, 1);
		return (0);
	}
	temp = first;
	while (temp)
	{
		if (temp->type == PIPE)
			ret = check_pipe_syntax(temp);
		else if (temp->type == REDIR)
			ret = check_redir_syntax(temp);
		if (ret == 0)
			return (ret);
		temp = temp->next;
	}
	return (ret);
}

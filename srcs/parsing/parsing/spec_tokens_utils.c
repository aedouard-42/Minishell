/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 23:01:32 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/09 23:01:50 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	spec_first_token_type(t_tokenl *first, int *key)
{
	if (ft_strcmp("<<", first->str) == 1 || ft_strcmp(">>", first->str) == 1
		|| ft_strcmp("<", first->str) == 1 || ft_strcmp(">", first->str) == 1)
		spec_redir(first);
	else if (first->str[0] == '|')
		first->type = PIPE;
	else
	{
		first->type = CMD;
		*key = 1;
	}
	return (1);
}

int	spec_last_token_type(t_tokenl *last, int key)
{
	if ((ft_strcmp("<<", last->str) == 1 || ft_strcmp(">>", last->str) == 1
			|| ft_strcmp("<", last->str) == 1 || ft_strcmp(">", last->str) == 1)
		&& last->str[0] != 0)
		last->type = REDIR;
	else if (last->str[0] == '|')
		last->type = PIPE;
	else
	{
		if (last->type != FILE)
		{
			if (key == 0)
				last->type = CMD;
			else
				last->type = ARG;
		}
	}
	return (1);
}

int	spec_last_first_token(t_tokenl *token, int *key)
{
	if (token->id == 1)
	{
		if (spec_first_token_type(token, key) == 0)
			return (0);
	}
	else
	{
		if (spec_last_token_type(token, *key) == 0)
			return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 14:45:09 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/09 23:01:17 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	spec_redir(t_tokenl *token)
{
	token->type = REDIR;
	if (token->next != NULL)
		token->next->type = FILE;
	return (1);
}

void	spec_cmd(t_tokenl *token, int *key)
{
	token->type = CMD;
	*key = 1;
	return ;
}

void	spec_pipe(t_tokenl *token, int *key)
{
	token->type = PIPE;
	*key = 0;
}

int	spec_types(t_tokenl *first)
{
	t_tokenl	*t;
	int			key;

	key = 0;
	t = first;
	while (t != NULL)
	{
		if (t->id == 1 || t->next == NULL)
		{
			if (spec_last_first_token(t, &key) == 0)
				return (0);
		}
		else if (ft_strcmp(t->str, "|") == 1 && t->str[0] != 0 && t->type != 6)
			spec_pipe(t, &key);
		else if ((ft_strcmp("<<", t->str) == 1 || ft_strcmp(">>", t->str) == 1
				|| ft_strcmp("<", t->str) == 1 || ft_strcmp(">", t->str) == 1)
			&& t->str[0] != 0 && t->type != QUOTED)
			spec_redir(t);
		else if (key == 0 && (t->type == NOSPEC || t->type == QUOTED))
			spec_cmd(t, &key);
		else if (key == 1 && (t->type == NOSPEC || t->type == QUOTED))
			t->type = ARG;
		t = t->next;
	}
	return (1);
}

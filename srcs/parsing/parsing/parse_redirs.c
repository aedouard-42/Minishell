/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:57:35 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/10 18:31:05 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_squotes(int *i, char *str, t_tokenl *last)
{
	const char	key = '\'';

	while (str[*i] && str[*i] != key)
	{
		last->str = ft_strjoin_char(last->str, str[*i]);
		if (last->str == NULL)
			return (0);
		*i = *i + 1;
	}
	*i = *i + 1;
	return (1);
}

int	add_quotes(int *i, char *str, t_tokenl *last, t_list **env)
{
	char	key;

	key = str[*i];
	*i = *i + 1;
	if (str[*i] == key)
	{
		*i = *i + 1;
		last->str = ft_strjoin_free_s1(last->str, NULL);
		if (last->str == NULL)
			return (0);
		return (1);
	}
	last->type = QUOTED;
	if (key == '\"')
		return (add_dquotes(i, str, last, env));
	else if (key == '\'')
		return (add_squotes(i, str, last));
	return (1);
}

int	addred_helper1(int *i, char *str, t_tokenl *last)
{
	while ((str[*i] == '<' || str[*i] == '>') && str[*i])
	{
		last->str = ft_strjoin_char(last->str, str[*i]);
		if (last->str == NULL)
			return (0);
		*i = *i + 1;
	}
	return (1);
}

int	addred_helper2(int *i, char *str, t_tokenl *last, t_list **env)
{
	while (ft_strchr(" <>|\t\n", str[*i]) == NULL && str[*i])
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			if (add_quotes(i, str, last, env) == 0)
				return (0);
		}
		else if (str[*i] == '$')
		{
			if (add_dollar(i, str, last, env) == 0)
				return (0);
		}
		else
		{
			last->str = ft_strjoin_char(last->str, str[*i]);
			if (last->str == NULL)
				return (0);
		}
		if (ft_strchr(" <>|\t\n", str[*i]) == NULL && str[*i])
			*i = *i + 1;
	}
	return (1);
}

int	add_redirs(t_tokenl **first, int *i, char *str, t_list **env)
{
	t_tokenl	*last;

	last = NULL;
	while (str[*i] != ' ' && str[*i] && str[*i] != '|')
	{
		last = ft_tokadd_back(first, ft_toknew());
		if (last == NULL)
			return (0);
		if (str[*i] == '<' || str[*i] == '>')
		{
			if (addred_helper1(i, str, last) == 0)
				return (0);
		}
		else if (str[*i] != '<' || str[*i] != '>')
			if (addred_helper2(i, str, last, env) == 0)
				return (0);
	}
	return (1);
}

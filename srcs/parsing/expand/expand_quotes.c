/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:39:38 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/09 22:41:21 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_dquotes(t_tokenl *last, int *i, char *str, t_list **env)
{
	*i = *i + 1;
	if (str[*i] == '\"')
	{
		last->str = ft_strjoin_char(last->str, '\0');
		if (last->str == NULL)
			return (0);
		return (1);
	}
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '$')
		{
			if (dollar_addqts(last, i, env, str) == 0)
				return (0);
		}
		else
		{
			last->str = ft_strjoin_char(last->str, str[*i]);
			if (last->str == NULL)
				return (0);
		}
		*i = *i + 1;
	}
	return (1);
}

int	expand_squotes(t_tokenl *last, int *i, char *str)
{
	*i = *i + 1;
	if (str[*i] == '\'')
	{
		last->str = ft_strjoin_char(last->str, '\0');
		if (last->str == NULL)
			return (0);
		return (1);
	}
	while (str[*i] && str[*i] != '\'')
	{
		last->str = ft_strjoin_char(last->str, str[*i]);
		if (last->str == NULL)
			return (0);
		*i = *i + 1;
	}
	return (1);
}

int	expand_quotes(t_tokenl *last, int *i, t_list **env, char *str)
{
	if (str[*i] == '\'')
		return (expand_squotes(last, i, str));
	else
		return (expand_dquotes(last, i, str, env));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:47:01 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/10 18:30:44 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_dquotes_helper(int *i, char *str, t_tokenl *last, t_list **env)
{
	if (ft_isdigit(str[*i + 1]) == 1)
	{
		if (dollar_fwd_by_digit(i, str, last, env) == 0)
			return (0);
		*i = *i - 1;
	}
	else
	{
		if (add_dollar_inquote(i, str, last, env) == 0)
			return (0);
	}
	return (1);
}

int	add_dquotes(int *i, char *str, t_tokenl *last, t_list **env)
{
	const char	key = '\"';

	while (str[*i] && str[*i] != key)
	{
		if (str[*i] == '$')
		{
			if (add_dquotes_helper(i, str, last, env) == 0)
				return (0);
		}
		if (str[*i] != key && str[*i])
		{
			last->str = ft_strjoin_char(last->str, str[*i]);
			if (last->str == NULL)
				return (0);
		}
		if (str[*i] && str[*i] != key && str[*i] != '$')
			*i = *i + 1;
	}
	*i = *i + 1;
	return (1);
}

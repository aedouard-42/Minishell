/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 07:12:25 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/10 18:30:38 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_fwd_by_digit(int *i, char *str, t_tokenl *last, t_list **env)
{
	char	*d_str;

	*i = *i + 1;
	d_str = ft_substr(str, *i, 1);
	if (d_str == NULL)
		return (0);
	d_str[0] = str[*i];
	*i = *i + 1;
	if (ft_search_value(*env, d_str) == NULL)
	{
		free(d_str);
		if (last->str == NULL)
			last->str = ft_strdup("");
		if (last->str == NULL)
			return (0);
		return (1);
	}
	last->str = ft_strjoin_free_s1(last->str, ft_search_value(*env, d_str));
	free(d_str);
	if (last->str == NULL)
		return (0);
	return (1);
}

int	dollar_add_exitsig(int *i, t_tokenl *last)
{
	last->str = ft_strjoin_free_s1(last->str,
			ft_itoa(g_exit_status));
	*i = *i + 1;
	if (last->str == NULL)
		return (0);
	return (1);
}

int	add_dollar_inquote(int *i, char *str, t_tokenl *last, t_list **env)
{
	char	*d_str;

	if (ft_isdigit((int)(str[*i + 1])) == 1)
		return (dollar_fwd_by_digit(i, str, last, env));
	*i = *i + 1;
	if (str[*i] == '?')
		return (dollar_add_exitsig(i, last));
	if (ft_strchr("|<>:$. /\'\"=", str[*i]) != NULL)
	{
		if (join_char_to_tok(last, str[*i]) == 0)
			return (0);
		return (1);
	}
	while (ft_strchr("<>|\"\' /:.$=", str[*i]) == NULL && str[*i])
	{
		d_str = ft_strjoin_char(d_str, str[*i]);
		if (d_str == NULL)
			return (0);
		*i = *i + 1;
	}
	last->str = ft_strjoin_free_s1(last->str, ft_search_value(*env, d_str));
	free(d_str);
	if (last->str == NULL)
		return (0);
	return (1);
}

int	add_dollar_helper(int *i, char *str, t_tokenl *last)
{
	if (str[*i] == '?')
		return (dollar_add_exitsig(i, last));
	if (str[*i] == '\'' || str[*i] == '\"')
		return (1);
	return (1);
}

int	add_dollar(int *i, char *str, t_tokenl *last, t_list **env)
{
	char	*d_str;

	if (ft_isdigit((int)(str[*i + 1])) == 1)
		return (dollar_fwd_by_digit(i, str, last, env));
	*i = *i + 1;
	if (ft_strchr("?\'\"", str[*i]) != NULL)
		return (add_dollar_helper(i, str, last));
	if (ft_isalnum(str[*i]) == 0 && str[*i] != '_')
	{
		if (join_char_to_tok(last, str[*i]) == 0)
			return (0);
		return (1);
	}
	while (ft_isalnum(str[*i]) == 0 && str[*i] != '_')
	{
		d_str = ft_strjoin_char(d_str, str[*i]);
		if (d_str == NULL)
			return (0);
		*i = *i + 1;
	}
	last->str = ft_strjoin_free_s1(last->str, ft_search_value(*env, d_str));
	free(d_str);
	if (last->str == NULL)
		return (0);
	return (1);
}

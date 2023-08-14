/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:44:12 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/09 22:44:33 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_is_digit(t_tokenl *last, int *i, char *str, t_list **env)
{
	char	*d_str;

	d_str = ft_substr(str, *i, 1);
	if (d_str == NULL)
		return (0);
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

int	dollar_addqts_helper(t_tokenl *last, int *i, t_list **env, char *str)
{
	if (str[*i] == '?')
		return (dollar_add_env_var(last));
	if (ft_isdigit((int)(str[*i])) == 1)
		return (dollar_is_digit(last, i, str, env));
	return (1);
}

int	dollar_addqts(t_tokenl *last, int *i, t_list **env, char *str)
{
	char	*d_str;

	*i = *i + 1;
	d_str = NULL;
	if (str[*i] == '?' || ft_isdigit((int)(str[*i])) == 1)
		return (dollar_addqts_helper(last, i, env, str));
	if (ft_isalnum(str[*i]) == 0 && str[*i] != '_')
	{
		if (join_char_to_tok(last, '$') == 0)
			return (0);
		return (1);
	}
	while (ft_isalnum(str[*i]) == 1 || str[*i] == '_')
	{
		d_str = ft_strjoin_char(d_str, str[*i]);
		if (d_str == NULL)
			return (0);
		*i = *i + 1;
	}
	*i = *i - 1;
	last->str = ft_strjoin_free_s1(last->str, ft_search_value(*env, d_str));
	free(d_str);
	if (last->str == NULL)
		return (0);
	return (1);
}

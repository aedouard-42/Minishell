/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:41:29 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/10 18:30:35 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_add_env_var(t_tokenl *last)
{
	char	*temp;

	temp = ft_itoa(g_exit_status);
	last->str = ft_strjoin_free_s1(last->str, temp);
	if (last->str == NULL)
		return (0);
	free(temp);
	return (1);
}

int	dollar_split_helper(t_tokenl **temp, t_tokenl *from, char *str, int *i)
{
	*temp = ft_toknew();
	if (*temp == NULL)
		return (0);
	(*temp)->id = from->id + 1000;
	(*temp)->type = ARG;
	if (str[*i] == ' ')
		skip_char(str, ' ', i);
	return (1);
}

int	dollar_add_split(t_tokenl **last, char *str, char **d)
{
	t_tokenl	*old_last;
	t_tokenl	*temp;
	int			i;

	i = 0;
	old_last = *last;
	skip_char(str, ' ', &i);
	while (str[i] && str[i] != ' ')
		if (join_char_to_tok(old_last, str[i++]) == 0)
			return (0);
	while (str[i])
	{
		if (dollar_split_helper(&temp, *last, str, &i) == 0)
			return (0);
		while (str[i] && str[i] != ' ')
			if (join_char_to_tok(temp, str[i++]) == 0)
				return (0);
		ft_tok_insert(old_last, temp);
		old_last = temp;
	}
	free(*d);
	*last = temp;
	return (1);
}

int	dollar_add_helper(t_tokenl **last, t_list **env, char **d)
{
	if (ft_search_value(*env, *d) != NULL)
		if (ft_strchr(ft_search_value(*env, *d), ' ') != NULL)
			return (dollar_add_split(last, ft_search_value(*env, *d), d));
	(*last)->str = ft_strjoin_free_s1((*last)->str, ft_search_value(*env, *d));
	free(*d);
	*d = NULL;
	if ((*last)->str == NULL)
		return (0);
	return (1);
}

int	dollar_add(t_tokenl **last, int *i, t_list **env, char *str)
{
	char	*d;

	d = NULL;
	*i = *i + 1;
	if (str[*i] == '?')
		return (dollar_add_env_var(*last));
	if (ft_isdigit((int)(str[*i])) == 1)
		return (dollar_is_digit(*last, i, str, env));
	if (ft_isalnum(str[*i]) == 0 && str[*i] != '_')
	{
		if (str[*i] == '\'' || str[*i] == '\"')
			return (join_char_to_tok((*last), '\0'));
		if (join_char_to_tok((*last), '$') == 0)
			return (0);
		return (1);
	}
	while (ft_isalnum(str[*i]) == 1 || str[*i] == '_')
	{
		d = ft_strjoin_char(d, str[*i]);
		if (d == NULL)
			return (0);
		*i = *i + 1;
	}
	*i = *i - 1;
	return (dollar_add_helper(last, env, &d));
}

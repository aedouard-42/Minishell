/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 14:04:38 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/10 21:31:14 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	join_char_to_tok(t_tokenl *token, char a)
{
	token->str = ft_strjoin_char(token->str, a);
	if (token->str == NULL)
		return (0);
	return (1);
}

int	quotes_add(t_tokenl *last, int *i, char *str)
{
	char	nbr;
	char	key;

	key = str[*i];
	nbr = 0;
	while (str[*i] && nbr != 2)
	{
		if (str[*i] == key)
			nbr++;
		last->str = ft_strjoin_char(last->str, str[*i]);
		if (last->str == NULL)
			return (0);
		if (nbr != 2)
			*i = *i + 1;
	}
	return (1);
}

int	token_add(t_tokenl **first, int *i, char *str)
{
	t_tokenl	*last;

	last = ft_tokadd_back(first, ft_toknew());
	if (last == NULL)
		return (0);
	while (ft_strchr("<>| \t\n", str[*i]) == NULL && str[*i])
	{
		if (str[*i] == '\"' || str[*i] == '\'')
		{
			if (quotes_add(last, i, str) == 0)
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

int	add_pipe(t_tokenl **first, int *i, char *str)
{
	t_tokenl	*last;

	last = ft_tokadd_back(first, ft_toknew());
	if (last == NULL)
		return (0);
	while (str[*i] == '|' && str[*i])
	{
		last->str = ft_strjoin_char(last->str, '|');
		if (last->str == NULL)
			return (0);
		*i = *i + 1;
	}
	return (1);
}

t_tokenl	*parce_cmd_line(char *str, t_list **lst_env)
{
	int			i;
	t_tokenl	*first;

	i = 0;
	first = NULL;
	while (str[i])
	{
		if (ft_strchr(" \t", str[i]) != NULL)
			skip_char(str, str[i], &i);
		if (str[i] == '<' || str[i] == '>')
		{
			if (add_redirs(&first, &i, str, lst_env) == 0)
				exit_parser(str, &first, lst_env);
		}
		else if (str[i] == '|')
		{
			if (add_pipe(&first, &i, str) == 0)
				exit_parser(str, &first, lst_env);
		}
		else if (str[i])
			if (token_add(&first, &i, str) == 0)
				exit_parser(str, &first, lst_env);
	}
	return (first);
}

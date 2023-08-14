/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:38:04 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/10 17:23:01 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_expander(t_tokenl **first, t_list **lst_env)
{
	ft_tokall_free(first);
	ft_lstclear(lst_env, *(ft_free_content));
	rl_clear_history();
	ft_putstr_fd(ERROR_MALLOC, 2);
	exit (127);
}

int	expand_word_starter(t_tokenl **last, char **str, int *i)
{
	*i = 0;
	*str = ft_strdup((*last)->str);
	if (*str == NULL)
		return (0);
	free((*last)->str);
	(*last)->str = NULL;
	return (1);
}

int	expand_word_finisher(char *str)
{
	free(str);
	return (1);
}

int	expand_word(t_tokenl **last, t_list **env, int i)
{
	char	*str;

	if (expand_word_starter(last, &str, &i) == 0)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (expand_quotes(*last, &i, env, str) == 0)
				return (0);
		}
		else if (str[i] == '$')
		{
			if (dollar_add(last, &i, env, str) == 0)
				return (0);
		}
		else
		{
			if (join_char_to_tok((*last), str[i]) == 0)
				return (0);
		}
		if (str[i] != 0)
			i++;
	}
	return (expand_word_finisher(str));
}

void	expand_words(t_tokenl **first, t_list **env)
{
	t_tokenl	*temp;
	t_tokenl	*t_next;
	int			i;

	temp = *first;
	while (temp)
	{
		t_next = temp->next;
		if (temp->type == ARG || temp->type == CMD || temp->type == FILE)
		{
			i = 0;
			if (expand_word(&temp, env, i) == 0)
				return (exit_expander(first, env));
		}
		temp = t_next;
	}
	return ;
}

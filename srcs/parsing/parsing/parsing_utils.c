/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:59:54 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/10 20:39:34 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_parser(char *str, t_tokenl **first, t_list **lst_env)
{
	ft_tokall_free(first);
	ft_lstclear(lst_env, *(ft_free_content));
	free(str);
	rl_clear_history();
	ft_putstr_fd(ERROR_MALLOC, 2);
	exit(127);
}

int	verif_line(char *str)
{
	int		i;
	char	key;
	int		closed;

	key = 0;
	closed = 1;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && closed == 1)
		{
			key = str[i];
			closed = 0;
		}
		else if (str[i] == key && closed == 0)
			closed = 1;
		i++;
	}
	if (line_contain_chars(str) == 0)
		return (0);
	if (closed == 1)
		return (1);
	g_exit_status = 2;
	ft_putstr_fd(OPEN_QUOTE, 1);
	return (0);
}

void	skip_char(char *str, char a, int *i)
{
	while (str[*i] == a && str[*i])
		*i = *i + 1;
	return ;
}

char	*ft_strjoin_free_helper(char *s1, char *s2, char **s3, int i)
{
	if (i >= 0)
	{
		(*s3)[i] = '\0';
		if (s1)
			free(s1);
		return (*s3);
	}
	else if (i < 0)
	{
		if (!s1 && !s2)
			*s3 = malloc(sizeof(char) * 1);
		else
			*s3 = malloc(sizeof(char) * (ft_strlen_p(s1)
						+ ft_strlen_p(s2) + 1));
		if (*s3 == NULL)
			return (NULL);
	}
	return (*s3);
}

char	*ft_strjoin_free_s1(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_strjoin_free_helper(s1, s2, &s3, -1) == NULL)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			s3[i] = s1[i];
			i++;
		}
	}
	if (s2)
	{
		while (s2[j])
			s3[i++] = s2[j++];
	}
	return (ft_strjoin_free_helper(s1, s2, &s3, i));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:35:31 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/11 00:10:39 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_char(char *str, char a)
{
	int		i;
	char	*ret;

	if (!str)
	{
		ret = malloc(2);
		if (ret == NULL)
			return (ret);
		ret[1] = 0;
		ret[0] = a;
		return (ret);
	}
	ret = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (ret == NULL)
		return (ret);
	i = 0;
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i++] = a;
	ret[i] = 0;
	free(str);
	return (ret);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen_p(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup_to(char *str, char a)
{
	int		i;
	int		size;
	char	*ret;

	i = 0;
	size = 0;
	while (str[size] != a && str[size])
		size++;
	ret = malloc(sizeof(char) * size + 1);
	if (ret == NULL)
		return (ret);
	while (i < size)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

int	get_fork_nbr(t_list *lst)
{
	int		ret;
	t_cmd	*cmd;

	cmd = (t_cmd *)(lst->content);
	ret = 0;
	if (cmd->next == NULL)
	{
		if (cmd->args == NULL)
			return (0);
		else if (is_builtin(cmd->args[0]))
			return (0);
		return (1);
	}
	while (lst)
	{
		if (((t_cmd *)lst->content)->args != NULL)
			ret++;
		lst = lst->next;
	}
	return (ret);
}

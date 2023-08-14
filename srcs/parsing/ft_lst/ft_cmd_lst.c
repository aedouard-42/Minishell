/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:53:49 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/09 13:54:54 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmdadd_back(t_cmd **begin_list, t_cmd *new)
{
	t_cmd	*ptr;

	if (*begin_list == 0)
		*begin_list = new;
	else
	{
		ptr = *begin_list;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

char	*null_string_array(char **arr)
{
	char	**temp;
	int		i;

	i = 0;
	temp = arr;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	if (temp)
		free(temp);
	return (NULL);
}

char	**load_args(t_tokenl *token)
{
	char		**args;
	t_tokenl	*temp;
	int			i;

	i = 0;
	args = malloc(sizeof(char *) * (get_arg_nbr(token) + 2));
	if (args == NULL)
		return (args);
	args[get_arg_nbr(token) + 1] = NULL;
	temp = token;
	while (temp)
	{
		if (temp->type == ARG || temp->type == CMD)
		{
			args[i] = ft_strdup(temp->str);
			if (args[i] == NULL)
				return ((char **)null_string_array(args));
			i++;
		}
		else if (temp->type == PIPE)
			return (args);
		temp = temp->next;
	}
	return (args);
}

int	is_cmd_in_pipe(t_tokenl *token)
{
	t_tokenl	*temp;

	temp = token;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == CMD)
			return (1);
		temp = temp->next;
	}
	return (0);
}

t_cmd	*ft_cmdnew(t_cmd **fst, t_tokenl *token, t_redir *red, t_list **env)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (ret == NULL)
		exit_get_lst(fst, token, env);
	if (is_cmd_in_pipe(token) == 0)
		ret->args = NULL;
	else
	{
		ret->args = load_args(token);
		if (ret->args == NULL)
			exit_get_lst(fst, token, env);
	}
	ret->fd[0] = 0;
	ret->fd[1] = 1;
	ret->redir = red;
	ret->next = NULL;
	return (ret);
}

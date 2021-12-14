/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:30:41 by aedouard          #+#    #+#             */
/*   Updated: 2021/11/09 11:30:42 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_name(char *str, char *name)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = ft_substr(str, 0, i);
	return	(name);
}

char *get_value_str(char *str, char *value)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	value = ft_substr(str, i + 1 , ft_strlen(str));
	return (value);
}

void	ft_lst_copyenv(char **env, t_list **head)
{
	int i;
	t_list *new;
	t_env_str *env_str;
	char *name;
	char *value;

	name = NULL;
	value = NULL;
	i = 0;
	while (env[i])
	{
		name = get_name(env[i], name);
		value = get_value_str(env[i], value);
		env_str = malloc(sizeof(*env_str));
		env_str->name = name;
		env_str->value = value;
		env_str->export = 1;
		new = ft_lstnew(env_str);
		ft_lstadd_back(head, new);
		i++;
	}
}
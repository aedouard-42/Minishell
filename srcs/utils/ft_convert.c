/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:35:12 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/10 19:54:04 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cat_elems(char *name, char *value)
{
	int		l_name;
	int		l_value;
	int		tot;
	char	*line;

	l_name = ft_strlen(name);
	l_value = ft_strlen(value);
	tot = l_name + l_value + 1;
	line = malloc(sizeof(char *) * tot);
	if (line == NULL)
		return (NULL);
	line[0] = '\0';
	ft_strlcat(line, name, tot + 1);
	ft_strlcat(line, "=", tot + 1);
	ft_strlcat(line, value, tot + 1);
	return (line);
}

int	get_export_size(t_list *lst)
{
	int			size;
	t_env_str	*content;

	size = 0;
	if (lst == NULL)
		return (0);
	while (lst)
	{
		content = (t_env_str *)lst->content;
		if (content->env_display == 1)
			size++;
		lst = lst->next;
	}
	return (size);
}

char	**ft_convert_exit(char **strs)
{
	ft_free_strs(strs);
	return (NULL);
}

char	**ft_convert(t_list *head)
{
	int			lst_size;
	t_env_str	*content;
	char		**envp;
	int			i;

	lst_size = get_export_size(head);
	i = 0;
	envp = (char **)ft_calloc(lst_size + 1, sizeof(char *));
	if (envp == NULL)
		return (NULL);
	while (head && lst_size != 0)
	{
		content = (t_env_str *)head->content;
		if (content->env_display == 1)
		{
			envp[i] = cat_elems(content->name, content->value);
			if (envp[i] == NULL)
				return (ft_convert_exit(envp));
			i++;
		}
		head = head->next;
	}
	envp[i] = NULL;
	return (envp);
}

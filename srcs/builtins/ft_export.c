/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:47:59 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/10 23:25:11 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	modify_var(t_list *list, char *name, char *value)
{
	t_env_str	*content;

	while (list)
	{
		content = (t_env_str *)list->content;
		if (found_in_env(name, list->content))
		{
			free(content->value);
			content->value = ft_strdup(value);
			content->env_display = 1;
			return ;
		}
		list = list->next;
	}
}

void	add_name_and_value(t_list *list, char *name, char *value, int _env)
{
	t_env_str	*content;
	t_list		*lst;

	content = malloc(sizeof(t_env_str));
	content->name = ft_strdup(name);
	content->value = ft_strdup(value);
	content->env_display = _env;
	lst = ft_lstnew(content);
	ft_lstadd_back(&list, lst);
}

void	export_to_list(char *str, t_list *env_lst, int export_env)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	name = get_name(str, name);
	value = get_value_str(str, value);
	if (ft_check_if_exists(env_lst, name))
	{
		if (export_env)
			modify_var(env_lst, name, value);
	}
	else if (export_env)
		add_name_and_value(env_lst, name, value, export_env);
	if (ft_check_if_exists(env_lst, name))
		modify_var(env_lst, name, value);
	else
		add_name_and_value(env_lst, name, value, export_env);
	free(name);
	free(value);
}

int	export_strs(char **strs, t_list *env_lst)
{
	int	i;
	int	status;
	int	export_env;

	i = 1;
	status = 0;
	while (strs[i])
	{
		export_env = check_export_validity(strs[i]);
		if (export_env == -1)
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(strs[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else
			export_to_list(strs[i], env_lst, export_env);
		i++;
	}
	return (status);
}

void	builtin_export(t_list *env_lst, char **strs)
{
	if (!strs || !strs[1])
	{
		ft_sort_export(env_lst);
		ft_lstiter(env_lst, print_export);
		g_exit_status = 0;
		return ;
	}
	g_exit_status = export_strs(strs, env_lst);
}

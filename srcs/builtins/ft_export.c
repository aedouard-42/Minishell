#include "../../includes/minishell.h"

int	check_export_validity(char *str)
{
	int i;
	int found_alpha;

	i = 0;
	found_alpha = 0;
	if (!str || !str[0] || str[0] == '=')
		return (-1);
	while (str[i] && str[i] != '=')
	{
		if (ft_isalpha(str[i]) == 1)
			found_alpha = 1;
		else
		{
			if (ft_isdigit(str[i]) && !found_alpha)
				return (-1);
			else if (!ft_isdigit(str[i]) && str[i] != '_')
				return (-1);
		}
		i++;
	}
	if (str[i] != '=')
		return (0);
	return (1);
}

void	modify_var(t_list *list, char *name, char *value)
{
	t_env_str *content;

	while (list)
	{
		content = (t_env_str *)list->content;
		if (found_in_env(name, list->content))
		{
			free(content->value);
			content->value = ft_strdup(value);
			return ;
		}
		list = list->next;
	}
}

void	add_name_and_value(t_list *list, char *name, char *value, int export_env)
{
	t_env_str *content;
	t_list *lst;

	content = malloc(sizeof(t_env_str));

	content->name = ft_strdup(name);
	content->value = ft_strdup(value);
	content->export = export_env;
	lst = ft_lstnew(content);
	ft_lstadd_back(&list, lst);
}

void	export_to_list(char *str, t_list *export_lst, t_list *env_lst, int export_env)
{
	char *name;
	char *value;

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
	if (ft_check_if_exists(export_lst, name))
		modify_var(export_lst, name, value);
	else
		add_name_and_value(export_lst, name, value, export_env);
	free(name);
	free(value);
}

void	builtin_export(t_list *export_lst, t_list *env_lst, char **strs)
{
	int i;
	int export_env;

	i = 0;
	if (!strs || !strs[1])
	{
		ft_sort_export(export_lst);
		builtin_env(export_lst);
	}
	while (strs[i])
	{
		export_env = check_export_validity(strs[i]);
		if (export_env == -1)
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(strs[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			errno = 1;
		}
		export_to_list(strs[i], export_lst, env_lst, export_env);
		i++;
	}
	errno = 0;
}
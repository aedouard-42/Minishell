/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acces.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 21:16:28 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/11 20:49:06 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_file(char *filename)
{
	int			ret;

	ret = access(filename, F_OK);
	if (ret != 0)
	{
		if (g_exit_status != 126)
			g_exit_status = 127;
		return (ret);
	}
	ret = access(filename, X_OK);
	if (ret != 0)
	{
		g_exit_status = 126;
		return (ret);
	}
	g_exit_status = 0;
	return (0);
}

int	try_access(char *cmd_name, t_list *env, char **test_path)
{
	char	**paths;
	int		i;
	int		access_return;

	i = 0;
	paths = get_paths(env);
	if (paths == NULL)
		return (1);
	while (paths[i])
	{
		*test_path = ft_strjoin(paths[i], cmd_name);
		access_return = is_valid_file(*test_path);
		if (access_return == 0)
		{
			free_paths(paths);
			return (0);
		}
		free(*test_path);
		*test_path = NULL;
		i++;
	}
	free_paths(paths);
	return (1);
}

int	check_absolute_access(char *str, char **path)
{
	if (is_valid_file(str) == 0)
	{
		*path = str;
		return (0);
	}
	return (1);
}

int	check_relative_access(char *str, t_list *env, char **path)
{
	int	granted;

	granted = try_access(str, env, path);
	return (granted);
}

int	check_acces_path(char *str, t_list *env, char **path)
{
	int	relative_path;
	int	absolute_path;

	if (!str || !*str)
	{
		g_exit_status = 127;
		return (1);
	}
	absolute_path = check_absolute_access(str, path);
	if (absolute_path == 0)
		return (absolute_path);
	relative_path = check_relative_access(str, env, path);
	return (relative_path);
}

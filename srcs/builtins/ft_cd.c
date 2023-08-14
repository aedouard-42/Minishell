/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:47:50 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/10 15:51:32 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	display_path_error(char *path)
{
	ft_putstr_fd("\033[0;31mMinishell$ \033[0;37mcd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(" No such file or directory\n", 2);
	return (1);
}

int	change_path(char *path, t_list *lst_env)
{
	char	*oldpwd;
	char	*newpwd;
	char	*tmp;
	int		ret;

	tmp = getcwd(NULL, 0);
	oldpwd = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	ret = chdir(path);
	if (ret == 0)
	{
		export_to_list(oldpwd, lst_env, 1);
		tmp = getcwd(NULL, 0);
		newpwd = ft_strjoin("PWD=", tmp);
		export_to_list(newpwd, lst_env, 1);
		free(newpwd);
		free(tmp);
	}
	else if (ret == -1)
		ret = display_path_error(path);
	free(oldpwd);
	return (ret);
}

int	change_home(t_list *lst_env, char **path)
{
	if (!ft_check_if_exists(lst_env, "HOME"))
	{
		ft_putstr_fd("\033[0;31mMinishell$ \033[0;37mcd: HOME not set\n", 2);
		return (1);
	}
	else
	{
		*path = ft_strdup(ft_search_value(lst_env, "HOME"));
		return (change_path(*path, lst_env));
	}
}

void	builtin_cd(char **args, t_list *lst_env)
{
	char	*path;

	path = NULL;
	if (args && args[1] && args[2])
	{
		ft_putstr_fd("\033[0;31mMinishell$ \033[0;37mcd: too many arguments\n", 2);
		g_exit_status = 1;
	}
	if (!args || !args[1])
		g_exit_status = change_home(lst_env, &path);
	else
	{
		path = ft_strdup(args[1]);
		g_exit_status = change_path(path, lst_env);
	}
	free(path);
}

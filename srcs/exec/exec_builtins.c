/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:14:43 by aedouard          #+#    #+#             */
/*   Updated: 2022/01/11 19:39:00 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char *s1, char *s2)
{
	int	n;

	if (!s1)
		return (0);
	n = ft_max(ft_strlen(s1), ft_strlen(s2));
	if (ft_strncmp(s1, s2, n) == 0)
		return (1);
	return (0);
}

int	is_builtin(char *str)
{
	if (check_builtin(str, BUILTIN_ECHO))
		return (1);
	if (check_builtin(str, BUILTIN_CD))
		return (1);
	if (check_builtin(str, BUILTIN_PWD))
		return (1);
	if (check_builtin(str, BUILTIN_EXPORT))
		return (1);
	if (check_builtin(str, BUILTIN_UNSET))
		return (1);
	if (check_builtin(str, BUILTIN_ENV))
		return (1);
	if (check_builtin(str, BUILTIN_EXIT))
		return (1);
	return (0);
}

int	run_builtin(char **args, t_list **env, t_data *data, int pid)
{
	if (check_builtin(args[0], BUILTIN_ECHO))
		builtin_echo(args);
	if (check_builtin(args[0], BUILTIN_CD))
		builtin_cd(args, *env);
	if (check_builtin(args[0], BUILTIN_PWD))
		builtin_pwd();
	if (check_builtin(args[0], BUILTIN_EXPORT))
		builtin_export(*env, args);
	if (check_builtin(args[0], BUILTIN_UNSET))
		builtin_unset(env, args);
	if (check_builtin(args[0], BUILTIN_ENV))
		builtin_env(*env);
	if (check_builtin(args[0], BUILTIN_EXIT))
		builtin_exit(args, data, pid);
	return (1);
}

int	exec_builtin(t_cmd *cmd, t_list **env, t_data *data)
{
	int	fd_out;
	int	fd_in;

	if (data->fork_nbr == 0 && (ft_strncmp("exit", cmd->args[0], 4) != 0))
	{
		fd_out = dup(STDOUT_FILENO);
		fd_in = dup(STDIN_FILENO);
	}
	if (redirect(cmd, 1, data) == -1)
		return (-1);
	run_builtin(cmd->args, env, data, 1);
	if (data->fork_nbr == 0)
	{
		dup2(fd_out, STDOUT_FILENO);
		dup2(fd_in, STDIN_FILENO);
		close(fd_out);
		close(fd_in);
	}
	return (1);
}

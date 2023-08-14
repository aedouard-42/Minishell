/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:20:35 by aedouard          #+#    #+#             */
/*   Updated: 2022/01/11 17:39:45 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_invalid_path(char *str, t_data *data)
{
	if (g_exit_status == 127)
	{
		ft_putstr_fd("Command not found : '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (g_exit_status == 126)
	{
		ft_putstr_fd("Permission denied : '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'\n", 2);
	}
	ft_exit(data, 0);
}

void	run_cmd(t_cmd *cmd, t_cmd *prev, t_cmd *next, t_data *data)
{
	char	*cmd_path;
	int		granted_acces;

	pipeflow(next, prev, cmd);
	redirect(cmd, 0, data);
	if (cmd->args)
	{	
		if (is_builtin(cmd->args[0]))
		{
			run_builtin(cmd->args, data->env_list, data, 0);
			if (prev)
				close(prev->fd[0]);
			ft_exit(data, 0);
		}
		granted_acces = check_acces_path(cmd->args[0],
				*(data->env_list), &cmd_path);
		if (granted_acces != 0)
		{
			if (prev)
				close(prev->fd[0]);
			exit_invalid_path(cmd->args[0], data);
		}
		execve(cmd_path, cmd->args, data->envp);
	}
	ft_exit(data, 0);
}

void	exec_cmd(t_cmd *cmd, t_cmd *prev, t_cmd *next_cmd, t_data *data)
{
	pid_t	pid;

	pipe(cmd->fd);
	pid = fork();
	if (pid != 0 && data->pids)
	{
		data->pids[data->index] = pid;
		data->index += 1;
	}
	signal_in_child();
	if (pid == 0)
		run_cmd(cmd, prev, next_cmd, data);
	else
	{
		close(cmd->fd[1]);
		if (prev)
			close(prev->fd[0]);
		if (!next_cmd)
			close (cmd->fd[0]);
	}
}

void	iter_cmds(t_list *lst, t_data *data)
{
	int		key;
	t_cmd	*temp[2];
	t_cmd	*cmd;

	temp[0] = NULL;
	temp[1] = NULL;
	while (lst)
	{
		key = 0;
		cmd = lst->content;
		temp[1] = (t_cmd *)lst->next;
		if (cmd->args)
		{
			if (is_builtin(cmd->args[0]) == 1 && temp[1] == NULL
				&& temp[0] == NULL)
			{
				key = 1;
				exec_builtin(cmd, data->env_list, data);
			}
		}
		if (key != 1)
			exec_cmd(cmd, temp[0], temp[1], data);
		temp[0] = lst->content;
		lst = lst->next;
	}
}

void	exec_cmds(t_list *lst, t_data *data)
{
	int	i;

	i = 0;
	iter_cmds(lst, data);
	while (i < data->fork_nbr)
	{
		waitpid(data->pids[i], &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
			g_exit_status = (unsigned char)(WEXITSTATUS(g_exit_status));
		else if (WIFSIGNALED(g_exit_status))
			g_exit_status = (unsigned char)(128 + WTERMSIG(g_exit_status));
		i++;
	}
}

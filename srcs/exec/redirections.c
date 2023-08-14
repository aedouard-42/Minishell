/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:42:37 by aedouard          #+#    #+#             */
/*   Updated: 2022/01/11 19:16:20 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_out(t_redir *redir, int *fd_out, int pid, t_data *data)
{
	*fd_out = open(redir->filename, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (*fd_out == -1)
	{
		perror(redir->filename);
		if (pid == 0)
			ft_exit(data, pid);
		else
			return (-1);
	}
	dup2(*fd_out, STDOUT_FILENO);
	close(*fd_out);
	return (0);
}

int	redir_in(t_redir *redir, int *fd_in, int pid, t_data *data)
{
	*fd_in = open(redir->filename, O_RDWR, S_IRWXU);
	if (*fd_in == -1)
	{
		perror(redir->filename);
		if (pid == 0)
			ft_exit(data, pid);
		else
			return (-1);
	}
	dup2(*fd_in, STDIN_FILENO);
	close(*fd_in);
	return (0);
}

int	redir_append(t_redir *redir, int *fd_out, int pid, t_data *data)
{
	*fd_out = open(redir->filename, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	if (*fd_out == -1)
	{
		perror(redir->filename);
		if (pid == 0)
			ft_exit(data, pid);
		else
			return (-1);
	}
	dup2(*fd_out, STDOUT_FILENO);
	close(*fd_out);
	return (0);
}

int	redir_heredoc(t_redir *redir, int *fd_in)
{
	int		ret;
	char	*str;
	int		n;

	ret = 1;
	signal_heredoc();
	*fd_in = open("tmp_heredoc", O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	while (ret)
	{
		str = readline(">");
		n = ft_strlen(str);
		if ((int)ft_strlen(redir->filename) > n)
			n = ft_strlen(redir->filename);
		ret = ft_strncmp(redir->filename, str, n);
		if (ret != 0)
		{
			write(*fd_in, ft_strjoin(str, "\n"), ft_strlen(str) + 1);
			*fd_in = open("tmp_heredoc", O_RDWR | O_APPEND, S_IRWXU);
		}
	}
	dup2(*fd_in, STDIN_FILENO);
	close (*fd_in);
	unlink("tmp_heredoc");
	return (0);
}

int	redirect(t_cmd *cmd, int pid, t_data *data)
{
	t_redir	*redir;
	int		fd_out;
	int		fd_in;
	int		ret;

	redir = cmd->redir;
	if (cmd->redir == NULL)
		return (1);
	while (redir)
	{
		if (redir->type == REDIR_OUT)
			ret = redir_out(redir, &fd_out, pid, data);
		else if (redir->type == REDIR_IN)
			ret = redir_in(redir, &fd_in, pid, data);
		else if (redir ->type == REDIR_OUT2)
			ret = redir_append(redir, &fd_out, pid, data);
		else if (redir->type == REDIR_IN2)
			ret = redir_heredoc(redir, &fd_in);
		if (ret == -1)
			return (ret);
				redir = redir->next;
	}
	return (1);
}

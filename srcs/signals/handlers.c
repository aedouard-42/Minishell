/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 00:16:26 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/11 19:18:37 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\n", 1);
		rl_redisplay();
		g_exit_status = 130;
		return ;
	}
}

void	handle_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		unlink("tmp_heredoc");
		g_exit_status = 130;
		close(STDIN_FILENO);
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("\n", 1);
		unlink("tmp_heredoc");
		exit(131);
		(void)sig;
	}
}

void	handle_child(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", 1);
		g_exit_status = 130;
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Minishell: Quit (core dumped)\n", 2);
		g_exit_status = 131;
	}
}

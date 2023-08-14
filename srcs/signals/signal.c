/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 00:16:37 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/11 18:36:37 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_in_main(void)
{
	signal(SIGINT, main_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	return ;
}

void	signal_in_child(void)
{
	signal(SIGINT, handle_child);
	signal(SIGQUIT, handle_child);
	return ;
}

void	signal_heredoc(void)
{
	signal(SIGINT, handle_heredoc);
	signal(SIGQUIT, handle_heredoc);
	return ;
}

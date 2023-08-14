/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeflow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 21:43:54 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/10 21:44:14 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipeflow(t_cmd *next, t_cmd *prev, t_cmd *cmd)
{
	if (next != NULL)
		dup2(cmd->fd[1], STDOUT_FILENO);
	if (prev != NULL)
		dup2(prev->fd[0], STDIN_FILENO);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
}

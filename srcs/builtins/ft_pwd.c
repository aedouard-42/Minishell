/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:15:53 by aedouard          #+#    #+#             */
/*   Updated: 2022/01/10 15:58:12 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(void)
{
	char	*buff;
	int		size;

	size = 1;
	buff = NULL;
	while (!buff)
	{
		buff = getcwd(buff, size);
		size += size;
	}
	printf("%s\n", buff);
	free(buff);
	g_exit_status = 0;
}

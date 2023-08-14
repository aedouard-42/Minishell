/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:19:05 by aedouard          #+#    #+#             */
/*   Updated: 2022/01/10 15:52:20 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
		i++;
	return (i);
}

int	check_new_line(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (1);
	if (ft_strncmp("-n", arg, 2) != 0)
		return (1);
	i += 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	builtin_echo(char **av)
{
	int	nl;
	int	ac;
	int	i;

	i = 1;
	ac = get_len(av);
	nl = check_new_line(av[1]);
	if (nl == 0)
		i++;
	while (i < ac)
	{
		printf("%s", av[i]);
		i++;
		if (i != ac)
			printf(" ");
	}
	if (nl)
		printf("\n");
	g_exit_status = 0;
}

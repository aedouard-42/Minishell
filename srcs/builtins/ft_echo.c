/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:19:05 by aedouard          #+#    #+#             */
/*   Updated: 2021/11/06 17:42:28 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_len(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
		i++;
	return (i);
}

void	builtin_echo(char **av)
{
	int	nl;
	int	ac;
	int	i;

	nl = 1;
	i = 1;
	ac = get_len(av);
	if (ac == 1)
		nl = 1;
	else if (ft_strncmp(av[1], "-n", ft_strlen(av[1])) == 0)
	{
		nl = 0;
		i++;
	}
	while (i < ac)
	{
		printf("%s", av[i]);
		i++;
		if (i != ac)
			printf(" ");
	}
	if (nl)
		printf("\n");
	errno = 0;
}

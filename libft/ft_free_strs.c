/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:39:17 by aedouard          #+#    #+#             */
/*   Updated: 2021/05/26 11:56:02 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split_strs(char **strs, int nb_strs)
{
	int	i;

	i = 0;
	while (i < nb_strs)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

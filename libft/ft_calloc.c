/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 10:13:39 by aedouard          #+#    #+#             */
/*   Updated: 2021/05/26 11:53:45 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	tot_size;

	tot_size = size * count;
	ptr = NULL;
	if (tot_size == 0)
		tot_size = 1;
	ptr = malloc(tot_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, tot_size);
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:36:13 by aedouard          #+#    #+#             */
/*   Updated: 2021/06/02 17:27:13 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	ldst;
	size_t	lsrc;

	i = 0;
	ldst = ft_strlen((dst));
	lsrc = ft_strlen((src));
	if (ldst > dstsize)
		return (lsrc + dstsize);
	while ((i + ldst) < dstsize - 1 && src[i])
	{
		dst[i + ldst] = src[i];
		i++;
	}
	dst[i + ldst] = '\0';
	return (lsrc + ldst);
}

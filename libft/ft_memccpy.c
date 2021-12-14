/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:46:19 by aedouard          #+#    #+#             */
/*   Updated: 2021/05/26 12:24:13 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*dstcpy;
	const unsigned char	*srccpy;

	srccpy = (const unsigned char *)src;
	dstcpy = (unsigned char *)dst;
	while (n)
	{
		*dstcpy = *srccpy;
		if (*srccpy == (unsigned char)c)
			return ((void *)(dstcpy + 1));
		srccpy++;
		dstcpy++;
		n--;
	}
	return (NULL);
}

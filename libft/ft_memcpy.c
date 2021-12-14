/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:27:42 by aedouard          #+#    #+#             */
/*   Updated: 2021/05/26 12:30:38 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dstcpy;
	const char	*srccpy;

	if (src == NULL && dst == NULL)
		return (NULL);
	srccpy = (const char *)src;
	dstcpy = (char *)dst;
	while (n)
	{
		*dstcpy = *srccpy;
		srccpy++;
		dstcpy++;
		n--;
	}
	return (dst);
}

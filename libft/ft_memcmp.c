/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:00:42 by aedouard          #+#    #+#             */
/*   Updated: 2021/05/26 12:30:06 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1cpy;
	unsigned char	*s2cpy;

	s1cpy = (unsigned char *)s1;
	s2cpy = (unsigned char *)s2;
	while (n)
	{
		if (*s1cpy != *s2cpy)
			return (*s1cpy - *s2cpy);
		s1cpy++;
		s2cpy++;
		n--;
	}
	return (0);
}

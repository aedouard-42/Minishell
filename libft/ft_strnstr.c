/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 18:24:55 by aedouard          #+#    #+#             */
/*   Updated: 2019/11/18 17:04:58 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char		*haycpy;
	size_t		n;

	haycpy = (char *)haystack;
	n = ft_strlen(needle);
	if (!*needle)
		return (haycpy);
	while (*haycpy && len)
	{
		if (*haycpy == *needle && n <= len)
		{
			if (!ft_strncmp(haycpy, needle, n))
				return (haycpy);
		}
		len--;
		haycpy++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:43:18 by aedouard          #+#    #+#             */
/*   Updated: 2021/06/02 18:15:30 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	s2 = malloc(sizeof(char) *(len + 1));
	if (!s2)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			s2[j] = s[i];
			j++;
		}
		i++;
	}
	s2[j] = '\0';
	return (s2);
}

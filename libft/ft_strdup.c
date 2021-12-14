/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 12:00:30 by aedouard          #+#    #+#             */
/*   Updated: 2021/06/02 17:23:45 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*scpy;
	int		len;
	int		i;

	len = ft_strlen(s1);
	i = 0;
	scpy = NULL;
	scpy = malloc(sizeof(char) * len + 1);
	if (!scpy)
		return (NULL);
	while (s1[i])
	{
		scpy[i] = (char)s1[i];
		i++;
	}
	scpy[i] = '\0';
	return (scpy);
}

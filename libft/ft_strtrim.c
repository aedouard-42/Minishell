/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:09:10 by aedouard          #+#    #+#             */
/*   Updated: 2021/06/02 17:35:33 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	inset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	findstart(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] && inset((char)s1[i], (char *)set))
		i++;
	return (i);
}

static int	findend(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1);
	while (i > 0 && (inset((char)s1[i - 1], (char *)set)))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	int		start;
	int		end;

	if (!s1 || !set)
		return (NULL);
	end = findend(s1, set);
	start = findstart(s1, set);
	s2 = ft_substr(s1, start, (end - start));
	return (s2);
}

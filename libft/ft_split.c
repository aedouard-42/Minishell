/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:40:11 by aedouard          #+#    #+#             */
/*   Updated: 2021/05/26 13:45:59 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	size_t	i;
	int		word;

	i = 0;
	word = 0;
	if (!c)
		return (1);
	while (s[i])
	{
		while (s[i] == c)
		{
			i++;
			if (i == ft_strlen(s))
				return (0);
		}
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c)
			i++;
		word++;
	}
	return (word);
}

static void	*ft_freestr(char **s2, int i)
{
	while (i)
	{
		i--;
		free(s2[i]);
		s2[i] = NULL;
	}
	free(s2);
	return (NULL);
}

static char	**mallocs2(const char *s, char c)
{
	int		word;
	char	**s2;

	s2 = NULL;
	if (!s)
		return (NULL);
	if (!s[0])
	{
		s2 = malloc(sizeof(char *));
		if (!s2)
			return (NULL);
		s2[0] = NULL;
		return (s2);
	}
	word = count_words(s, c);
	s2 = malloc(sizeof(char *) * (word + 1));
	if (!s2)
		return (NULL);
	s2[word] = NULL;
	return (s2);
}

static char	**ft_init_split_vars(int *i, int *start, const char *s, char c)
{
	char	**s2;

	*start = 0;
	*i = 0;
	s2 = mallocs2(s, c);
	return (s2);
}

char	**ft_split(char const *s, char c)
{
	int		word;
	char	**s2;
	int		start;
	int		end;
	int		i;

	s2 = ft_init_split_vars(&i, &start, s, c);
	word = count_words(s, c);
	if (!s2)
		return (NULL);
	while (i < word && s[start])
	{
		while (s[start] == c && s[start])
			start++;
		end = start;
		while (s[end] != c && s[end])
			end++;
		s2[i] = ft_substr(s, start, (end - start));
		if (!s2[i])
			return (ft_freestr(s2, i));
		i++;
		start = end + 1;
	}
	return (s2);
}

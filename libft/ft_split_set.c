/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 18:35:07 by aedouard          #+#    #+#             */
/*   Updated: 2021/09/12 18:35:14 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char *set)
{
	size_t	i;
	int		word_count;

	word_count = 0;
	i = 0;
	if (set == NULL)
		return (1);
	while (s[i])
	{
		while (s[i] && ft_inset(s[i], set))
		{
			i++;
			if (i == ft_strlen(s))
				return (0);
		}
		while (s[i] && !ft_inset(s[i], set))
			i++;
		while (s[i] && ft_inset(s[i], set))
			i++;
		word_count++;
	}
	return (word_count);
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

static void	fill_strs(char *s, char **s2, int word_count, char *set)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	while (i < word_count && s[start])
	{
		while (s[start] && ft_inset(s[start], set))
			start++;
		end = start;
		while (s[end] && !ft_inset(s[end], set))
			end++;
		s2[i] = ft_substr(s, start, (end - start));
		if (!s2[i])
		{
			ft_freestr(s2, i);
			return ;
		}
		i++;
		start = end + 1;
	}
}

char	**ft_split_set(char *s, char *set)
{
	char	**s2;
	int		word_count;

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
	word_count = count_words(s, set);
	s2 = malloc(sizeof(char *) * (word_count + 1));
	if (!s2)
		return (NULL);
	s2[word_count] = NULL;
	fill_strs(s, s2, word_count, set);
	return (s2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:59:16 by aedouard          #+#    #+#             */
/*   Updated: 2021/05/26 12:02:22 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getlen(long n)
{
	int		len;

	len = 0;
	if (n == 0)
		len = 1;
	while (n)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static char	*fill(char *s, long n, int neg, int len)
{
	s[len + 1] = '\0';
	if (n == 0)
		s[len] = '0';
	while (n)
	{
		s[len] = n % 10 + '0';
		len--;
		n = n / 10;
	}
	if (neg)
		s[len] = '-';
	return (s);
}

static int	isneg(long n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	int		neg;
	int		len;
	char	*s;
	long	nb;

	nb = (long)n;
	len = getlen(nb);
	neg = isneg(nb);
	s = NULL;
	if (neg)
	{
		nb = -nb;
		len = len + 1;
	}
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	s = fill(s, nb, neg, len - 1);
	return (s);
}

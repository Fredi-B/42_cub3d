/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 14:49:40 by fbechtol          #+#    #+#             */
/*   Updated: 2021/07/21 14:59:33 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_pow(int len)
{
	int	x;

	x = 1;
	while (len)
	{
		x *= 10;
		len--;
	}
	return (x);
}

static int	n_len(int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*strfill(char *s, int len, int n, int i)
{
	while (len)
	{
		s[i] = n / my_pow(len - 1) + '0';
		n %= my_pow(len - 1);
		i++;
		len--;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = 0;
	len = n_len(n);
	if (n < 0 || n == -0)
	{
		s = (char *)malloc(len + 1 + 1);
		if (!s)
			return (0);
		s[0] = '-';
		if (n == 0)
			s[0] = '0';
		n *= -1;
		i = 1;
	}
	else
	{
		s = (char *)malloc(len + 1);
		i = 0;
	}
	return (strfill(s, len, n, i));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 13:39:13 by fbechtol          #+#    #+#             */
/*   Updated: 2021/11/24 15:08:43 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*isspacechar(const char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	return ((str));
}

static const char	*issign(const char *str, int *sign)
{
	int	i;

	i = 0;
	if (*str == '-' || *str == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		str++;
	}
	return (str);
}

void	isnbr(const char *str)
{
	if (*str < '0' || *str > '9')
	{
		write(2, "Error\n", 6);
		exit(2);
	}
}

int	ft_atoi(const char *str)
{
	size_t	i;
	long	nbr;
	int		sign;

	str = isspacechar(str);
	sign = 1;
	str = issign(str, &sign);
	nbr = 0;
	i = 0;
	isnbr(str);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nbr <= 2147483648)
			nbr = nbr * 10 + str[i] - '0';
		else
			break ;
		i++;
	}
	if (nbr * sign > 2147483647 || nbr * sign < -2147483648 \
		|| str[i] != '\0')
	{
		write(2, "Error\n", 6);
		exit(2);
	}
	return (sign * nbr);
}

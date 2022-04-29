/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 17:12:50 by fbechtol          #+#    #+#             */
/*   Updated: 2021/07/06 17:52:08 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbrlen(int n);
static int	hardcode(int n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	int		j;
	char	digit[11];

	if (hardcode(n, fd))
		return ;
	if (n < 0 && n)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	i = nbrlen(n);
	j = i;
	while (i != 0)
	{
		digit[i - 1] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	write(fd, digit, j);
}

static int	hardcode(int n, int fd)
{
	if (n == 0)
	{
		write(fd, "0", 1);
		return (1);
	}
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (1);
	}
	return (0);
}

static int	nbrlen(int n)
{
	int	i;
	int	j;

	i = 0;
	j = n;
	while (j != 0)
	{
		j /= 10;
		i++;
	}
	return (i);
}

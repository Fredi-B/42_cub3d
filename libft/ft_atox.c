/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:59:01 by fbechtol          #+#    #+#             */
/*   Updated: 2021/11/22 13:38:08 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_atox(const char *str)
{
	int				i;
	unsigned int	nbr;

	if (str == NULL)
		return (-1);
	str = &str[2];
	nbr = 0;
	i = 0;
	while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'f') \
			|| (str[i] >= 'A' && str[i] <= 'F'))
	{
		if (str[i] >= '0' && str[i] <= '9')
			nbr = nbr * 16 + str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			nbr = nbr * 16 + str[i] - ('a' - 10);
		else
			nbr = nbr * 16 + str[i] - ('A' - 10);
		i++;
	}
	return (nbr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 11:45:08 by fbechtol          #+#    #+#             */
/*   Updated: 2021/07/21 13:11:28 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n) && *(unsigned char *)(s1 + i) == *(unsigned char *)(s2 + i))
	{
		i++;
		if (i == n)
			return (0);
	}
	return ((*(unsigned char *)(s1 + i)) - (*(unsigned char *)(s2 + i)));
}

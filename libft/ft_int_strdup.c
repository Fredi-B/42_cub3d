/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_strdup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:15:57 by fbechtol          #+#    #+#             */
/*   Updated: 2021/12/03 10:55:53 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_int_strdup(const int *s, int len)
{
	int	*dup;

	dup = (int *)malloc(sizeof(*dup) * len);
	if (!dup)
		return (0);
	ft_int_memcpy(dup, s, len);
	return (dup);
}

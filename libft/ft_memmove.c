/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:14:42 by fbechtol          #+#    #+#             */
/*   Updated: 2021/07/21 11:32:03 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*u_src;
	unsigned char	*u_dst;
	size_t			i;

	u_src = (unsigned char *)src;
	u_dst = (unsigned char *)dst;
	if (!dst && !src)
		return (0);
	i = 0;
	if (dst < src)
	{
		while (i < len)
		{
			u_dst[i] = u_src[i];
			i++;
		}
	}
	else
	{
		while (len--)
			u_dst[len] = u_src[len];
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_backwards.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:08:50 by fbechtol          #+#    #+#             */
/*   Updated: 2022/04/30 19:21:47 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp_backwards(const char *s1, const char *s2, size_t n)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = 0;
	while (len_s1 > i && len_s2 > i && i < n && s1[len_s1] == s2[len_s2])
	{
		i++;
		len_s1--;
		len_s2--;
	}
	return ((unsigned char)*(s1 + len_s1) - (unsigned char)*(s2 + len_s2));
}

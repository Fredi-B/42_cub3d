/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmp_file_extension.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:40:03 by fbechtol          #+#    #+#             */
/*   Updated: 2022/05/25 12:48:57 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_cmp_file_extension(const char *s1, const char *s2, size_t len)
{
	char	**splitted_path;
	int		i;

	splitted_path = ft_split(s1, '/');
	i = 0;
	while (splitted_path[i + 1])
		i++;
	if (ft_strncmp_backwards(splitted_path[i], s2, len) != 0 \
		|| ft_strlen(splitted_path[i]) <= len)
		return (false);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmp_file_extension.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:40:03 by fbechtol          #+#    #+#             */
/*   Updated: 2022/04/30 20:23:51 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_cmp_file_extension(const char *s1, const char *s2, size_t len)
{
	if (ft_strlen(s1) <= len || ft_strncmp_backwards(s1, s2, len) != 0)
		return (false);
	return (true);
}

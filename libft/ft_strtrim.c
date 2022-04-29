/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 11:09:49 by fbechtol          #+#    #+#             */
/*   Updated: 2021/07/21 14:36:48 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_trim_front(char const *s1, char const *set, \
	size_t len_front, size_t s_len);
static size_t	ft_trim_back(char const *s1, char const *set, size_t len_back);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len_front;
	size_t	len_back;
	size_t	s_len;

	if (!s1)
		return (0);
	len_front = 0;
	s_len = ft_strlen(s1);
	len_front = ft_trim_front(s1, set, len_front, s_len);
	len_back = s_len;
	if (len_front < s_len)
		len_back = ft_trim_back(s1, set, len_back);
	return (ft_substr(s1, len_front, s_len - len_front - (s_len - len_back)));
}

static size_t	ft_trim_front(char const *s1, char const *set, \
	size_t len_front, size_t s_len)
{
	size_t	i;

	i = 0;
	while (set[i] && len_front < s_len)
	{
		i++;
		if (s1[len_front] == set[i - 1])
		{
			len_front++;
			i = 0;
		}
	}
	return (len_front);
}

static size_t	ft_trim_back(char const *s1, char const *set, size_t len_back)
{
	size_t	i;

	i = 0;
	while (set[i] && len_back > 0)
	{
		i++;
		if (s1[len_back - 1] == set[i - 1])
		{
			len_back--;
			i = 0;
		}
	}
	return (len_back);
}

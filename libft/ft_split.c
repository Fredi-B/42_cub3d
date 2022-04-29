/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:34:15 by fbechtol          #+#    #+#             */
/*   Updated: 2022/01/17 17:07:45 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_str_count(char const *s, char c);
static void		ft_splitted_str(char **arr, char const *s, char c, \
	size_t count);

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**arr;

	if (!s)
		return (NULL);
	count = ft_str_count(s, c);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	ft_splitted_str(arr, s, c, count);
	return (arr);
}

static size_t	ft_str_count(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

/* first while (s[j]) loop to get to the start of the substring, next to get
	to the end */
static void	ft_splitted_str(char **arr, char const *s, char c, size_t count)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (i < count)
	{
		while (s[j] == c && s[j])
			j++;
		start = j;
		while (s[j] != c && s[j])
			j++;
		arr[i] = ft_substr(s, start, j - start);
		i++;
	}
	arr[i] = NULL;
}

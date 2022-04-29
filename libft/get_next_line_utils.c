/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 15:09:17 by fbechtol          #+#    #+#             */
/*   Updated: 2021/08/17 17:07:19 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//size_t	ft_strlen(const char *s)
//{
//	size_t	i;
//
//	i = 0;
//	while (s[i])
//		i++;
//	return (i);
//}
//
//char	*ft_strjoin(char const *s1, char const *s2)
//{
//	char	*s3;
//	int		i;
//	int		j;
//
//	if (s1 == NULL)
//		return (NULL);
//	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
//	if (s3 == NULL)
//		return (NULL);
//	i = 0;
//	while (s1[i])
//	{
//		s3[i] = s1[i];
//		i++;
//	}
//	j = 0;
//	while (s2[j])
//	{
//		s3[i] = s2[j];
//		j++;
//		i++;
//	}
//	s3[i] = '\0';
//	return (s3);
//}
//
//char	*ft_strchr(const char *s, int c)
//{
//	int		i;
//
//	i = 0;
//	while (s[i] != '\0')
//	{
//		if (s[i] == c)
//			return ((char *)(s + i));
//		i++;
//	}
//	return (NULL);
//}
//
//char	*ft_substr(char const *s, unsigned int start, size_t len)
//{
//	size_t	i;
//	size_t	s_len;
//	char	*substr;
//
//	if (!s)
//		return (0);
//	s_len = ft_strlen(s);
//	substr = malloc(len + 1);
//	if (!substr)
//		return (0);
//	i = 0;
//	while (len--)
//	{
//		if (s[i] && start <= s_len)
//		{
//			substr[i] = s[i + start];
//			i++;
//		}
//	}
//	substr[i] = '\0';
//	return (substr);
//}
//
//char	*ft_strdup(const char *s)
//{
//	int		i;
//	char	*dup;
//
//	i = 0;
//	dup = malloc(ft_strlen(s) + 1);
//	if (dup == NULL)
//		return (NULL);
//	while (s[i] != '\0')
//	{
//		dup[i] = s[i];
//		i++;
//	}
//	dup[i] = '\0';
//	return (dup);
//}

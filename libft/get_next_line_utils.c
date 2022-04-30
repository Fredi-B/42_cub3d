/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 11:44:58 by afey              #+#    #+#             */
/*   Updated: 2022/04/30 12:52:31 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	size_t	slen;
	size_t	i;

	slen = ft_strlen_gnl(s);
	i = 0;
	while (i < slen)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

char	*ft_strjoin_gnl(char const *save, char const *line)
{
	char	*str;
	size_t	i;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen_gnl(save);
	len2 = ft_strlen_gnl(line);
	str = (char *)malloc ((len1 + len2 + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (len1 > 0 && save[i] != '\0')
	{
		str[i] = save[i];
		i++;
	}
	while (line[i - len1] != '\0')
	{
		str[i] = line[i - len1];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup_gnl(const char *s1)
{
	char	*str;
	size_t	len;
	size_t	i;

	len = ft_strlen_gnl(s1);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*substr;

	if (!s)
		return (0);
	s_len = ft_strlen_gnl(s);
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (0);
	i = 0;
	while (len--)
	{
		if (s[i] && start <= s_len)
		{
			substr[i] = s[i + start];
			i++;
		}
	}
	substr[i] = '\0';
	return (substr);
}

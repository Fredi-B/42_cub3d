/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 12:03:27 by fbechtol          #+#    #+#             */
/*   Updated: 2021/07/12 14:53:23 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* using ft_strdup to allocate memory */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*mapi;
	unsigned int	i;

	if (!s)
		return (0);
	mapi = ft_strdup(s);
	if (!mapi)
		return (0);
	i = 0;
	while (mapi[i])
	{
		mapi[i] = f(i, s[i]);
		i++;
	}
	return (mapi);
}

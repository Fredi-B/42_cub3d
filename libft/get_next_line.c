/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 15:09:33 by fbechtol          #+#    #+#             */
/*   Updated: 2021/11/16 12:11:34 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <signal.h>

/* read fd into buf and joining stat and buf til nl is found or n_read is 0. */
char	*get_next_line(int fd)
{
	char		*buf;
	static char	*stat = "\0";
	int			n_read;

	if (stat == NULL || fd < 0)
		return (NULL);
	n_read = 1;
	while (n_read >= 0)
	{
		buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return (NULL);
		n_read = read(fd, buf, BUFFER_SIZE);
		if (n_read < 0)
		{
			free(buf);
			return (NULL);
		}
		join_read(&buf, &stat, n_read);
		if (ft_strchr(stat, '\n'))
			return (get_line(&stat));
		if (n_read == 0)
			return (NULL);
	}
	return (NULL);
}

/* join stat and buf. Free stat if not first call */
void	join_read(char **buf, char **stat, int n_read)
{
	char		*tmp;
	static int	first_call = YES;

	buf[0][n_read] = '\0';
	tmp = ft_strjoin(*stat, *buf);
	free(*buf);
	if (first_call == NO)
		free(*stat);
	*stat = tmp;
	first_call = NO;
}

/* free and update stat. Return line */
char	*get_line(char **stat)
{
	char	*line;
	char	*tmp;

	line = ft_substr(*stat, 0, ft_strchr(*stat, '\n') - *stat + 1);
	tmp = ft_strdup(ft_strchr(*stat, '\n') + 1);
	free(*stat);
	*stat = tmp;
	return (line);
}

/* free stat and return last_line if there's one */
char	*get_last_line(char **stat)
{
	char	*last_line;

	if (*stat[0] == '\0')
	{
		free(*stat);
		*stat = NULL;
		return (NULL);
	}
	last_line = ft_strdup(*stat);
	free(*stat);
	*stat = NULL;
	return (last_line);
}

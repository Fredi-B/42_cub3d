/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afey <afey@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 11:44:51 by afey              #+#    #+#             */
/*   Updated: 2021/12/28 11:44:52 by afey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*ft_check(char **pt_save, char *line, int i)
{
	char	*tmp;

	line = ft_substr_gnl(*pt_save, 0, i + 1);
	tmp = ft_strdup_gnl(&((*pt_save)[i + 1]));
	free(*pt_save);
	*pt_save = tmp;
	if ((*pt_save)[0] == '\0')
	{
		free(*pt_save);
		*pt_save = NULL;
	}
	return (line);
}

static char	*ft_get_line(char **pt_save, int sz)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	if (sz == 0 && *pt_save == NULL)
		return (NULL);
	i = 0;
	while ((*pt_save)[i] != '\0' && (*pt_save)[i] != '\n')
		i++;
	if ((*pt_save)[i] == '\0')
	{
		tmp = ft_strdup_gnl(*pt_save);
		free(*pt_save);
		*pt_save = NULL;
	}
	else
		tmp = ft_check(pt_save, tmp, i);
	return (tmp);
}

static void	ft_tojoin(char **pt_save, char *line)
{
	char	*tmp;

	tmp = ft_strjoin_gnl(*pt_save, line);
	free(*pt_save);
	*pt_save = tmp;
}

static void	*ft_free(char *line)
{
	free (line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;
	int			sz;

	line = (char *) malloc((1 + 1) * sizeof(char));
	if (!line || fd < 0)
		return (ft_free(line));
	sz = 1;
	while (sz > 0)
	{
		sz = read(fd, line, 1);
		if (sz < 0)
			return (ft_free(line));
		else if (sz == 0)
			break ;
		line[sz] = '\0';
		if (!save)
			save = ft_strdup_gnl(line);
		else
			ft_tojoin(&save, line);
		if (ft_strchr_gnl(save, '\n'))
			break ;
	}
	free (line);
	return (ft_get_line(&save, sz));
}

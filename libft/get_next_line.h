/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 16:37:57 by fbechtol          #+#    #+#             */
/*   Updated: 2021/11/15 10:19:27 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* ----------------------------- Includes ---------------------------------- */

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

/* ----------------------------- Defines ---------------------------------- */

# define YES 0
# define NO 1
# define BUFFER_SIZE 1

/*  ------------------------ Function prototypes --------------------------- */

char	*get_next_line(int fd);
void	join_read(char **buf, char **stat, int n_read);
char	*get_line(char **stat);
char	*get_last_line(char **stat);
//char	*ft_strdup(const char *s);
//char	*ft_strjoin(char const *s1, char const *s2);
//size_t	ft_strlen(const char *s);
//char	*ft_strchr(const char *s, int c);
//char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif

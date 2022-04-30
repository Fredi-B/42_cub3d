#ifndef CUB3D_H
# define CUB3D_H
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>

/* get_next_line.c get_next_line_utils.c*/
char	*get_next_line(int fd);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);
char	*ft_strchr_gnl(const char *s, int c);
size_t	ft_strlen_gnl(const char *str);
char	*ft_strdup_gnl(const char *s1);
char	*ft_strjoin_gnl(char const *save, char const *line);

#endif

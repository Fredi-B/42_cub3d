#include "cub3D.h"

int	read_file(char *file, t_data *arr)
{
	int		fd;
	char	*line;
	char	**split;

	fd = open(file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line || line[0] == '\n')
			break ;
		split = ft_split_cnt(line, ' ', &(arr->cols));
		arr->rows++;
//		ft_resize(&*arr);
		free(line);
		free_2D(split);
	}
	close(fd);
	return (OK);
}
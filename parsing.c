#include "cub3D.h"

int	parsing(t_data *data, char **argv)
{
	if (ft_strncmp_backwards(argv[1], ".cub\0", 4) != 0)
		err_exit(data, "Wrong file extension", 21, 1);
	return (0);
}
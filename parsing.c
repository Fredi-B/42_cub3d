#include "cub3D.h"

int	parsing(t_data *data, char **argv)
{
	if (ft_cmp_file_extension(argv[1], ".cub", 4) == false)
		err_exit(data, "Wrong file extension", 21, 1);
	return (0);
}

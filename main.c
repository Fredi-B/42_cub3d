#include "cub3D.h"

int	main(int argc __attribute__ ((unused)), char **argv)
{
	t_data	data;

	if (argc != 2)
		err_exit(&data, "Wrong number of arguments", 26, 1);
	parsing(&data, argv);
	map_init(&data);
	draw_map(&data);
	return (OK);
}

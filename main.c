#include "cub3D.h"

static void	init_data(t_data *data);

int	main(int argc __attribute__ ((unused)), char **argv)
{
	t_data	data;

	if (argc != 2)
		err_exit(&data, "Wrong number of arguments", 26, 1);
	init_data(&data);
	parsing(&data, argv);
	map_init(&data);
	draw_map(&data);
	return (OK);
}

static void	init_data(t_data *data)
{
	int	i;

	data->map = NULL;
	data->north = NULL;
	data->south = NULL;
	data->west = NULL;
	data->east = NULL;
	data->num = NULL;
	data->mlx = NULL;
	data->mlx_window = NULL;
	data->img = NULL;
	data->addr = NULL;
	i = 0;
	while (i < 4)
	{
		data->wall[i].img = NULL;
		data->wall[i].addr = NULL;
		i++;
	}
	data->xpm_file.img = NULL;
	data->xpm_file.addr = NULL;
	data->first_person_view.img = NULL;
	data->first_person_view.addr = NULL;
	data->minimap.img = NULL;
	data-> minimap.addr = NULL;
	data->player_in_minimap.img = NULL;
	data->player_in_minimap.addr = NULL;
}

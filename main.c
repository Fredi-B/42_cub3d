#include "cub3D.h"

static void	init_data(t_data *data);
static void	init_key_flags(t_data *data);
static void	init_xpm(t_data *data);

void	check_leaks(void)
{
	system("leaks cub3D");
}

int	main(int argc __attribute__ ((unused)), char **argv)
{
	t_data	data;

	// atexit(check_leaks);
	if (argc != 2)
		err_exit(&data, "Wrong number of arguments", 26, 1);
	init_data(&data);
	parsing(&data, argv);
	map_init(&data);
	draw_map(&data);
	key_hooks(&data);
	mlx_loop(data.mlx);
	free_data(&data);
	return (OK);
}

static void	init_data(t_data *data)
{
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
	data->img_map = NULL;
	data->addr_map = NULL;
	data->first_person_view.img = NULL;
	data->first_person_view.addr = NULL;
	data->minimap.img = NULL;
	data-> minimap.addr = NULL;
	init_key_flags(data);
	init_xpm(data);
}

static void	init_key_flags(t_data *data)
{
	data->key_flag.up = OFF;
	data->key_flag.down = OFF;
	data->key_flag.left = OFF;
	data->key_flag.right = OFF;
}

static void	init_xpm(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->wall[i].img = NULL;
		data->wall[i].addr = NULL;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		data->xpm_file[i].img = NULL;
		data->xpm_file[i].addr = NULL;
		i++;
	}
}

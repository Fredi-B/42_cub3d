#include "cub3D.h"

void	destroy_window(t_data *arr)
{
	mlx_destroy_image(arr->mlx, arr->img);
	mlx_destroy_window(arr->mlx, arr->mlx_window);
	free_arr(arr);
	exit(0);
}

void	map_to_image(t_data *arr)
{
	mlx_clear_window(arr->mlx, arr->mlx_window);
	arr->img = mlx_new_image(arr->mlx, arr->width, arr->height);
	if (arr->img == NULL)
		err_exit(arr, "Error: could not create mlx image", 33, 1);
	arr->addr = mlx_get_data_addr(arr->img, &arr->bits_per_pixel, \
								&arr->size_line, &arr->endian);
}

static int	main_loop(t_data *arr)
{
	t_line	line;

	move(arr);
	mlx_do_sync(arr->mlx);
	init_line(&line);
	get_rays(arr, &line);
	mlx_put_image_to_window(arr->mlx, arr->mlx_window, \
							arr->img, 0, 0);
	return (0);
}

bool	draw_map(t_data *arr)
{
	arr->mlx = mlx_init();
	if (!arr->mlx)
		destroy_window(arr);
	arr->mlx_window = mlx_new_window(arr->mlx, arr->width, \
											arr->height, "cub3D");
	if (!arr->mlx_window)
		err_exit(arr, "Could not create new_window", 27, 1);
	if (put_walls_in_images(arr) == false)
		return (false);
	map_to_image(arr);
	mlx_loop_hook(arr->mlx, &main_loop, arr);
	return (true);
}

#include "cub3D.h"

void	get_map_2(t_data *arr, t_line *line, int row, int col)
{
	int		i;
	t_points p0, p1;

	i = 0;
	while (i < arr->subsize -1)
	{
		if (arr->map[row * arr->cols + col] == '1')
			p0.color = GREEN;
		else
			p0.color = BLACK;
		p0.x = col * arr->subsize + i +1;
		p0.y = row * arr->subsize +1;
		p1.x = p0.x;
		p1.y = p0.y + arr->subsize -2;
		p1.color = p0.color; 
		set_line(line, arr, p0, p1);
		i++;
	}
}

static void	get_map(t_data *arr, t_line *line)
{
	int	row;
	int	col;

	row = 0;
	while (row < arr->rows)
	{
		col = 0;
		while (col < arr->cols)
		{
			get_map_2(arr, line, row, col);
			col++;
		}
		row++;
	}
}

void	destroy_window(t_data *arr)
{
	mlx_destroy_image(arr->mlx, arr->img);
	mlx_destroy_image(arr->mlx, arr->img_map);
	mlx_destroy_window(arr->mlx, arr->mlx_window);
	free_arr(arr);
	exit(0);
}
	/* system("leaks fdf"); */

/* same as pixel_is_inside_image() but with t_data * as argument.
if we put mlx variables for the main image in the t_image struct
this function gets obsolete */
bool	pixel_is_inside_window(int x, int y, t_data *arr)
{
	if (x < 0 || x > arr->width -1) // not sure why -1
		return (false);
	if (y < 0 || y > arr->height -1)
		return (false);
	return (true);
}

void	pixel_put(t_data *arr, int x, int y, int color)
{
	char	*dst;
	// diprintf(x);
	// diprintf(y);
	// diprintf(arr->width);
	if (arr->map_flag == 1)
	{
		if (x % arr->scale_map || y % arr->scale_map)
			return ;
		x = x / arr->scale_map;
		y = y / arr->scale_map;
		dst = arr->addr_map + (y * arr->size_line_map + x * \
								(arr->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	 	return ;
	}
	if (pixel_is_inside_window(x, y, arr) == true)
	{
		dst = arr->addr + (y * arr->size_line + x * \
								(arr->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	map_to_image(t_data *arr)
{
	t_line			line;

	mlx_clear_window(arr->mlx, arr->mlx_window);
	arr->img = mlx_new_image(arr->mlx, arr->width, arr->height);
	arr->addr = mlx_get_data_addr(arr->img, &arr->bits_per_pixel, \
								&arr->size_line, &arr->endian);

	arr->img_map = mlx_new_image(arr->mlx, arr->cols * arr->subsize / arr->scale_map, arr->rows * arr->subsize / arr->scale_map);
	arr->addr_map = mlx_get_data_addr(arr->img_map, &arr->bits_per_pixel, \
								&arr->size_line_map, &arr->endian);
	init_line(&line);
	arr->map_flag = 1;
	get_map(arr, &line);
	get_player(arr, &line);
	get_rays(arr, &line);

}

void	all_images_to_window(t_data *arr)
{
	mlx_put_image_to_window(arr->mlx, arr->mlx_window, \
							arr->img, 0, 0);
	mlx_put_image_to_window(arr->mlx, arr->mlx_window, \
							arr->img_map, 0, 0);
	// mlx_put_image_to_window(arr->mlx, arr->mlx_window, arr->xpm_file[WEST].img, 500, 500);
	// mlx_put_image_to_window(arr->mlx, arr->mlx_window, arr->wall[SOUTH].img, 0, 0);
}

void	draw_map(t_data *arr)
{
	arr->mlx = mlx_init();
	if (!arr->mlx)
		destroy_window(arr);

	arr->mlx_window = mlx_new_window(arr->mlx, arr->width, \
											arr->height, "cub3D");
	
	put_walls_in_images(arr);

	map_to_image(arr);
	all_images_to_window(arr);

}

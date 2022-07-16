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
		// malt die map noch an der 'falschen' Stelle. d.h. nicht zentriert um den fixen player drum rum.
		// p0.x = ((col * arr->subsize + i +1) - (arr->p_x / 64));
		// p0.y = ((row * arr->subsize +1) - (arr->p_y / 64));
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
	// malt nur noch die map, die um den player drum rum ist
	int	start_row;
	int	start_col;
	int	end_row;
	int	end_col;

	start_row = (arr->p_y / 64) - 8 ;
	if (start_row < 0)
		start_row = 0;
	end_row = start_row + 16;
	if (end_row > arr->rows)
		end_row = arr->rows;
	while (start_row < end_row)
	{
		start_col = (arr->p_x / 64) - 8;
		if (start_col < 0)
			start_col = 0;
		end_col = start_col + 16;
		if (end_col > arr->cols)
			end_col = arr->cols;
		while (start_col < end_col)
		{
			get_map_2(arr, line, start_row, start_col);
			start_col++;
		}
		start_row++;
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
/* same as pixel_is_inside_window() but for minimap. */
bool	pixel_is_inside_minimap(int x, int y, t_data *arr)
{
	// diprintf(y);
	// diprintf(arr->minimap_height);
	if (x < 0 || x > arr->minimap_width -1 || x > arr->width -1) // not sure why -1
		return (false);
	if (y < 0 || y > arr->minimap_height -1 || y > arr->height -1)
		return (false);
	return (true);
}

void	pixel_put(t_data *arr, int x, int y, int color)
{
	char	*dst;
	// diprintf(x);
	// diprintf(y);
	// diprintf(arr->width);
	if (arr->map_flag == ON)
	{
		if (x % arr->scale_map || y % arr->scale_map)
			return ;
		x = x / arr->scale_map;
		y = y / arr->scale_map;
		if (pixel_is_inside_minimap(x, y, arr) == true)
		{
			dst = arr->addr_map + (y * arr->size_line_map + x * \
									(arr->bits_per_pixel / 8));
			*(unsigned int *)dst = color;
	 		return ;
		}
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
	// mlx_clear_window(arr->mlx, arr->mlx_window);
	arr->img = mlx_new_image(arr->mlx, arr->width, arr->height);
	if (arr->img == NULL)
		err_exit(arr, "Error: could not create mlx image", 33, 1);
	arr->addr = mlx_get_data_addr(arr->img, &arr->bits_per_pixel, \
								&arr->size_line, &arr->endian);
	arr->minimap_width = 5 * arr->subsize;
	arr->minimap_height = 5 * arr->subsize;
	// exception has occured (auch wenn nicht direkt an wand.
	// Löschen wir die images richtig?)
	arr->img_map = mlx_new_image(arr->mlx,arr->minimap_width, arr->minimap_height);
	if (arr->img_map == NULL)
		err_exit(arr, "Error: could not create mlx image", 33, 1);
	arr->addr_map = mlx_get_data_addr(arr->img_map, &arr->bits_per_pixel, \
								&arr->size_line_map, &arr->endian);
}

void	all_images_to_window(t_data *arr)
{
	mlx_put_image_to_window(arr->mlx, arr->mlx_window, \
							arr->img, 0, 0);
	if (arr->draw_map_flag == ON)
		mlx_put_image_to_window(arr->mlx, arr->mlx_window, \
							arr->img_map, 0, 0);
	// mlx_put_image_to_window(arr->mlx, arr->mlx_window, arr->xpm_file[WEST].img, 500, 500);
	// mlx_put_image_to_window(arr->mlx, arr->mlx_window, arr->wall[SOUTH].img, 0, 0);
}

static int	main_loop(t_data *arr)
{
	t_line	line;

	move(arr);
	mlx_do_sync(arr->mlx);
	init_line(&line);
	arr->map_flag = ON;
	if (arr->draw_map_flag == ON)
		get_map(arr, &line);
	get_player(arr, &line);
	get_rays(arr, &line);
	all_images_to_window(arr);
	return (0);
}

bool	draw_map(t_data *arr)
{
	arr->mlx = mlx_init();
	if (!arr->mlx)
		destroy_window(arr);

	arr->mlx_window = mlx_new_window(arr->mlx, arr->width, \
											arr->height, "cub3D");
	
	if (put_walls_in_images(arr) == false)
		return (false);

	map_to_image(arr);
	mlx_loop_hook(arr->mlx, &main_loop, arr);

	return (true);
}

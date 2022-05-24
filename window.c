#include "cub3D.h"

void	get_map_2(t_data *arr, t_line *line, int row, int col)
{
	int		i;
	t_points p0, p1;

	i = 0;
	while (i < arr->subsize -1)
	{
		if (arr->map[row * arr->cols + col] == '1')
			p0.color = WHITE;
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

int	destroy_window(t_data *arr)
{
	mlx_destroy_image(arr->mlx, arr->img);
	mlx_destroy_window(arr->mlx, arr->mlx_window);
	free_arr(arr);
	exit(0);
	return (0);
}
	/* system("leaks fdf"); */

void	pixel_put(t_data *arr, int x, int y, int color)
{
	char	*dst;

	dst = arr->addr + (y * arr->size_line + x * \
							(arr->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	map_to_image(t_data *arr)
{
	t_line			line;

	mlx_clear_window(arr->mlx, arr->mlx_window);
	arr->img = mlx_new_image(arr->mlx, arr->width, arr->height);
	arr->addr = mlx_get_data_addr(arr->img, &arr->bits_per_pixel, \
								&arr->size_line, &arr->endian);
	// init_line(&line);
	// get_map(arr, &line);
	//get_player(arr, &line);
	//get_rays(arr, &line);
	mlx_put_image_to_window(arr->mlx, arr->mlx_window, \
							arr->img, 0, 0);
	return ;
}

void	draw_map(t_data *arr)
{
	arr->mlx = mlx_init();
	//if (!arr->mlx) AUF FEHLER TESTEN!
	//	destroy_window(arr);
	arr->width = 300;
	arr->height = 300;

	arr->mlx_window = mlx_new_window(arr->mlx, arr->width, \
											arr->height, "cub3D");
	
	map_to_image(arr);
	// mlx_key_hook(arr->mlx_window, hook, arr);
	mlx_loop(arr->mlx);
}

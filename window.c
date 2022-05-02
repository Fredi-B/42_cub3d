#include "cub3D.h"

void	get_map_2(t_array *arr, t_line *line, int row, int col)
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

static void	get_map(t_array *arr, t_line *line)
{
	size_t	row;
	size_t	col;

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

int	destroy_window(t_array *arr)
{
	mlx_close_window(arr->mlx);
	mlx_delete_image(arr->mlx, arr->img);
	mlx_terminate(arr->mlx);
	//mlx_destroy_image(arr->mlx, arr->img);
	//mlx_destroy_window(arr->mlx, arr->mlx_window);
	free_arr(arr);
	exit(0);
	return (0);
}
	/* system("leaks cub3D"); */

void	pixel_put(t_array *arr, int x, int y, int color)
{
	/* char	*dst;

	dst = arr->addr + (y * arr->size_line + x * \
							(arr->bits_per_pixel / 8));
	*(unsigned int *)dst = color; */
//WHITE = 0xFFFFFFFF
	mlx_put_pixel(arr->img, x, y, color); // Single white pixel in the middle.

}

void	map_to_image(t_array *arr)
{
	t_line			line;

	mlx_delete_image(arr->mlx, arr->img); //hier noch altes bild irgendwie loschen
	arr->img = mlx_new_image(arr->mlx, arr->width, arr->height);
	init_line(&line);
	get_map(arr, &line);
	get_player(arr, &line);
	get_rays(arr, &line);
	mlx_put_pixel(arr->img, 10, 10, 0xFF00FFFF); // TESTEST
	mlx_image_to_window(arr->mlx, arr->img, 0, 0);
}

//called from main.c
void	draw_map(t_array *arr)
{
	arr->mlx = mlx_init(arr->width, arr->height, "CUB3D", true);

	if (!arr->mlx)
		destroy_window(arr);
	map_to_image(arr);
	mlx_loop_hook(arr->mlx, &hook, arr);
	mlx_loop(arr->mlx);
}
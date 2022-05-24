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

void	*my_new_image(void *mlx, int size, t_image *copy)
{
	copy->img = mlx_new_image(mlx, size, size);
	if (copy->img == NULL)
		return (NULL);
	copy->addr = mlx_get_data_addr(copy->img, &copy->bits_per_pixel, &copy->line_length, &copy->endian);
	copy->width = size;
	copy->height = size;
	return (copy->img);
}

int	get_pixel_color(t_image *original, int x, int y)
{
	int	color;

// protecten mit is_inside_image_limits()
	color = BLACK;
	color = *(unsigned int *)(original->addr + (unsigned int)(int)y * original->line_length + x * (original->bits_per_pixel / 8));
	return (color);
}

int	get_color_from_texture(t_image *original, int x, int y, int size)
{
	int	color;
	float	scale_x;
	float	scale_y;
	float	tx;
	float	ty;

	scale_x = original->width / (float)size;
	scale_y = original->height / (float)size;
	tx = x * scale_x;
	ty = y * scale_y;
	color = get_pixel_color(original, tx, ty);
	return (color);
}

// same as pixel_put() but with t_image * instead of t_data *
void	my_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;
	
// protecten mit is_inside_image_limits()
	dst = img->addr + (y * img->line_length + x * \
							(img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	resize_texture(void *mlx, t_image *original, t_image *copy, int size)
{
	int	y;
	int	x;
	int	color;

	copy->img = my_new_image(mlx, size, copy);
	if (copy->img == NULL)
		return ; //protecten
	y = 0;
	while (y < copy->height)
	{
		x = 0;
		while (x < copy->width)
		{
			color = get_color_from_texture(original, x, y, size);
			my_pixel_put(copy, x, y, color);
			x++;
		}
		y++;
	}
	
}

void	map_to_image(t_data *arr)
{
	t_line			line;
	t_image			*deer;
	t_image			*copy;
	char	*path = "deer.xpm";

	mlx_clear_window(arr->mlx, arr->mlx_window);
	// arr->img = mlx_new_image(arr->mlx, arr->width, arr->height);
	// arr->addr = mlx_get_data_addr(arr->img, &arr->bits_per_pixel, \
	// 							&arr->size_line, &arr->endian);
	// init_line(&line);
	// get_map(arr, &line);
	// get_player(arr, &line);
	// get_rays(arr, &line);

	deer = malloc(sizeof(t_image));
	copy = malloc(sizeof(t_image));
	deer->img = mlx_xpm_file_to_image(arr->mlx, path, &deer->width, &deer->height);
	if (deer->img == NULL)
		return ; //protecten
	deer->addr = mlx_get_data_addr(deer->img, &deer->bits_per_pixel, &deer->line_length, &deer->endian);
	if (deer->addr == NULL)
		return ; //protecten
	resize_texture(arr->mlx, deer, copy, 100);

	mlx_put_image_to_window(arr->mlx, arr->mlx_window, deer->img, 500, 500);
	mlx_put_image_to_window(arr->mlx, arr->mlx_window, copy->img, 0, 0);
	// mlx_put_image_to_window(arr->mlx, arr->mlx_window, \
	// 						arr->img, 0, 0);
	return ;
}

void	draw_map(t_data *arr)
{
	arr->mlx = mlx_init();
	//if (!arr->mlx) AUF FEHLER TESTEN!
	//	destroy_window(arr);
	// arr->width = 1920;
	// arr->height = 1080;

	arr->mlx_window = mlx_new_window(arr->mlx, arr->width, \
											arr->height, "cub3D");
	
	map_to_image(arr);
	mlx_key_hook(arr->mlx_window, hook, arr);
	mlx_loop(arr->mlx);
}

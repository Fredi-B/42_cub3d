#include "cub3D.h"

static bool	put_wall_in_image(t_data *arr, int side, char *direction);
static void	resize_texture(void *mlx, t_image *original, \
							t_image *copy, int size);
static int	get_color_from_texture(t_image *original, int x, int y, int size);
static int	get_pixel_color(t_image *original, int x, int y);

bool	put_walls_in_images(t_data *arr)
{
	put_wall_in_image(arr, NORTH, arr->north);
	put_wall_in_image(arr, EAST, arr->east);
	put_wall_in_image(arr, WEST, arr->west);
	put_wall_in_image(arr, SOUTH, arr->south);

	return (true);
}

static bool	put_wall_in_image(t_data *arr, int side, char *direction)
{
	arr->xpm_file[side].img = mlx_xpm_file_to_image(arr->mlx, \
						direction, &arr->xpm_file[side].width, &arr->xpm_file[side].height);
	if (arr->xpm_file[side].img == NULL)
		return (false);
	arr->xpm_file[side].addr = mlx_get_data_addr \
						(arr->xpm_file[side].img, &arr->xpm_file[side].bits_per_pixel, \
						&arr->xpm_file[side].line_length, &arr->xpm_file[side].endian);
	if (arr->xpm_file[side].addr == NULL)
		return (false);
	resize_texture(arr->mlx, &arr->xpm_file[side], &arr->wall[side], 100);
	// mlx_destroy_image(arr->mlx, arr->xpm_file[side].img);
	return (true);
}

static void	resize_texture(void *mlx, t_image *original, \
								t_image *copy, int size)
{
	int	y;
	int	x;
	int	color;

	copy->img = my_new_image(mlx, size, copy);
	if (copy->img == NULL)
		return ; //wie protecten?
	y = 0;
	while (y < copy->height)
	{
		x = 0;
		while (x < copy->width)
		{
			color = get_color_from_texture(original, x, y, size);
			image_pixel_put(copy, x, y, color);
			x++;
		}
		y++;
	}
}

static int	get_color_from_texture(t_image *original, int x, int y, int size)
{
	int		color;
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

static int	get_pixel_color(t_image *original, int x, int y)
{
	int	color;

	if (pixel_is_inside_image(x, y, original) == false)
		return (color);
	color = BLACK;
	color = *(unsigned int *)(original->addr \
			+ (unsigned int)(int)y * original->line_length + x \
			* (original->bits_per_pixel / 8));
	return (color);
}

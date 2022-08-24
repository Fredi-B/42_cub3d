#include "cub3D.h"

static bool	put_wall_in_image(t_data *arr, int side, char *direction);
static bool	resize_texture(void *mlx, t_image *original, \
							t_image *copy, int x_and_y[2]);
static int	get_color_from_texture(t_image *original, int x, \
											int y, int x_and_y[2]);
static int	get_pixel_color(t_image *original, int x, int y);

bool	put_walls_in_images(t_data *arr)
{
	if (put_wall_in_image(arr, NORTH, arr->north) == false)
		return (false);
	if (put_wall_in_image(arr, EAST, arr->east) == false)
		return (false);
	if (put_wall_in_image(arr, WEST, arr->west) == false)
		return (false);
	if (put_wall_in_image(arr, SOUTH, arr->south) == false)
		return (false);
	return (true);
}

static bool	put_wall_in_image(t_data *arr, int side, char *direction)
{
	int	x_and_y[2];

	arr->xpm_file[side].img = mlx_xpm_file_to_image(arr->mlx, direction, \
					&arr->xpm_file[side].width, &arr->xpm_file[side].height);
	if (arr->xpm_file[side].img == NULL)
		return (false);
	arr->xpm_file[side].addr = mlx_get_data_addr (arr->xpm_file[side].img, \
		&arr->xpm_file[side].bits_per_pixel, &arr->xpm_file[side].line_length, \
		&arr->xpm_file[side].endian);
	if (arr->xpm_file[side].addr == NULL)
		return (false);
	x_and_y[0] = 200;
	x_and_y[1] = 200;
	resize_texture(arr->mlx, &arr->xpm_file[side], &arr->wall[side], x_and_y);
	// mlx_destroy_image(arr->mlx, arr->xpm_file[side].img); // von fred: brauchen wir das?
	return (true);
}

static bool	resize_texture(void *mlx, t_image *original, \
								t_image *copy, int x_and_y[2])
{
	int	y;
	int	x;
	int	color;

	copy->img = my_new_image(mlx, x_and_y[0], x_and_y[1], copy);
	if (copy->img == NULL)
		return (false);
	y = 0;
	while (y < copy->height)
	{
		x = 0;
		while (x < copy->width)
		{
			color = get_color_from_texture(original, x, y, x_and_y);
			image_pixel_put(copy, x, y, color);
			x++;
		}
		y++;
	}
	return (true);
}

static int	get_color_from_texture(t_image *original, int x, \
											int y, int x_and_y[2])
{
	int		color;
	float	scale_x;
	float	scale_y;
	float	tx;
	float	ty;

	scale_x = original->width / (float)x_and_y[0];
	scale_y = original->height / (float)x_and_y[1];
	tx = x * scale_x;
	ty = y * scale_y;
	color = get_pixel_color(original, tx, ty);
	return (color);
}

static int	get_pixel_color(t_image *original, int x, int y)
{
	int	color;

	color = BLACK;
	if (pixel_is_inside_image(x, y, original) == false)
		return (color);
	color = *(unsigned int *)(original->addr \
			+ (unsigned int)(int)y * original->line_length + x \
			* (original->bits_per_pixel / 8));
	return (color);
}

#include "cub3D.h"

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

static int	get_color_from_imageatx(t_image *original, int *image_start_x, float line_h, t_data *data, int r)
{
	int		color;
	float	scale;
	float	tx;
	float	ty;
	int		y;

	scale = (float) original->height / line_h;
	tx = (float) *image_start_x / data->subsize * original->width;
	y = 0;
	ty = 0;
	while (ty < original->height)
	{
		ty = y * scale;
		color = get_pixel_color(original, (int) tx, (int) ty);
		pixel_put(data, r, data->height * 0.5 - line_h * 0.5 + y, color);
		y++;
	}
	return (OK);
}

static void	adjust_startx(int *direction, int *image_start_x, t_data *data)
{
	int	tmp;

	if (*direction == NORTH)
		return ;
	else if (*direction == EAST)
		return ;
	else if (*direction == SOUTH)
	{
		tmp = data->subsize - 1 - *image_start_x;
		*image_start_x = tmp;
		return ;
	}
	else if (*direction == WEST)
	{
		tmp = data->subsize - 1 - *image_start_x;
		*image_start_x = tmp;
		return ;
	}
}

void	draw_wall_line(int *direction, int *image_start_x, float line_h, t_data *data, int r)
{
	adjust_startx(direction, image_start_x, data);
	get_color_from_imageatx(&data->wall[*direction], image_start_x, line_h, data, r);
	return ;
}

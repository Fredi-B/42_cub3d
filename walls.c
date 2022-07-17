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

static int	get_color_imageatx(t_image *orig, float line_h, t_data *data, int r)
{
	int		color;
	float	scale;
	float	tx;
	float	ty;
	int		y;

	scale = (float) orig->height / line_h;
	tx = (float) data->image_x / data->subsize * orig->width;
	y = 0;
	ty = 0;
	while (ty < orig->height)
	{
		ty = y * scale;
		color = get_pixel_color(orig, (int) tx, (int) ty);
		pixel_put(data, r, data->height * 0.5 - line_h * 0.5 + y, color);
		y++;
	}
	return (OK);
}

static void	adjust_startx(t_data *data)
{
	int	tmp;

	if (data->direction == NORTH)
		return ;
	else if (data->direction == EAST)
		return ;
	else if (data->direction == SOUTH)
	{
		tmp = data->subsize - 1 - data->image_x;
		data->image_x = tmp;
		return ;
	}
	else if (data->direction == WEST)
	{
		tmp = data->subsize - 1 - data->image_x;
		data->image_x = tmp;
		return ;
	}
}

void	draw_wall_line(float line_h, t_data *data, int r)
{
	adjust_startx(data);
	get_color_imageatx(&data->wall[data->direction], line_h, data, r);
	return ;
}

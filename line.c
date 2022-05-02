#include "cub3D.h"

static int	init_var_s(int x0, int x1)
{
	if (x0 < x1)
		return (1);
	else
		return (-1);
}

void	ft_plot_pixel(t_array *arr, t_line *line, int n_pixel)
{
	if (line->color0 != line->color1)
	{
		pixel_put(arr, line->x0, line->y0, (((line->color0 * arr->i) + \
				(line->color1 * arr->j)) / n_pixel));
		arr->i--;
		arr->j++;
	}
	else
	{
		pixel_put(arr, line->x0, line->y0, line->color0);
	}
}

void	set_line(t_line *line, t_array *arr, t_points p0, t_points p1)
{
	line->x0 = p0.x;
	line->y0 = p0.y;
	line->color0 = p0.color;
	line->x1 = p1.x;
	line->y1 = p1.y;
	line->color1 = p1.color;
	line->sx = init_var_s(line->x0, line->x1);
	line->sy = init_var_s(line->y0, line->y1);
	line->dx = abs(line->x1 - line->x0);
	line->dy = -abs(line->y1 - line->y0);
	line->err = line->dx + line->dy;
	draw_line(line, arr);
}

void	draw_line_loop(t_line *line, t_array *arr, int *n_pixel)
{
	while (1)
	{
		if (*n_pixel > 0)
			ft_plot_pixel(arr, line, *n_pixel);
		else
			*n_pixel = *n_pixel - 1;
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
		line->e2 = 2 * line->err;
		if (line->e2 > line->dy)
		{
			line->err += line->dy;
			line->x0 += line->sx;
		}
		if (line->e2 < line->dx)
		{
			line->err += line->dx;
			line->y0 += line->sy;
		}
	}
	if (*n_pixel < 0)
		*n_pixel = *n_pixel * -1 - 1;
}

void	draw_line(t_line *line, t_array *arr)
{
	int	n_pixel;
	int	tmp_x0;
	int	tmp_y0;

	n_pixel = 0;
	tmp_x0 = line->x0;
	tmp_y0 = line->y0;
	draw_line_loop(line, arr, &n_pixel);
	line->x0 = tmp_x0;
	line->y0 = tmp_y0;
	if (n_pixel == 0)
		n_pixel = 1;
	arr->i = n_pixel;
	arr->j = 0;
	draw_line_loop(line, arr, &n_pixel);
}

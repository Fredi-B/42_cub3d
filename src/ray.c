#include "cub3D.h"

/* returns distance of ray for horizontal walls */
float	dist_horizontal(t_points *ph, t_data *arr, float ra)
{
	float	box[5];

	ph->color = WHITE;
	box[TAN] = calc_atan(ra);
	if (ra == 0 || ra == M_PI)
		return (1000000);
	else if (ra < M_PI)
	{
		box[RY] = (((int)arr->p_y >> arr->sub_bit) << arr->sub_bit) - 0.1;
		box[RX] = (arr->p_y - box[RY]) * box[TAN] + arr->p_x;
		box[YO] = -arr->subsize;
		box[XO] = -box[YO] * box[TAN];
		arr->direction = 0;
	}
	else if (ra > M_PI)
	{
		box[RY] = (((int)arr->p_y >> arr->sub_bit) << arr->sub_bit) \
				+ arr->subsize;
		box[RX] = (arr->p_y - box[RY]) * box[TAN] + arr->p_x;
		box[YO] = arr->subsize;
		box[XO] = -box[YO] * box[TAN];
		arr->direction = 2;
	}
	return (calc_dist(arr, ph, box));
}

/* returns distance of ray for vertical walls */
float	dist_vertical(t_points *pv, t_data *arr, float ra)
{
	float	box[5];

	pv->color = WHITE;
	box[TAN] = calc_ntan(ra);
	if (ra == 0 || ra == M_PI)
		return (1000000);
	else if (ra < M_PI * 0.5 || ra > M_PI * 1.5)
	{
		box[RX] = (((int)arr->p_x >> arr->sub_bit) << arr->sub_bit) - 0.1;
		box[RY] = (arr->p_x - box[RX]) * box[TAN] + arr->p_y;
		box[XO] = -arr->subsize;
		box[YO] = -box[XO] * box[TAN];
		arr->direction = arr->direction + 30;
	}
	else if (ra > M_PI * 0.5 && ra < M_PI * 1.5)
	{
		box[RX] = (((int)arr->p_x >> arr->sub_bit) << arr->sub_bit) \
				+ arr->subsize;
		box[RY] = (arr->p_x - box[RX]) * box[TAN] + arr->p_y;
		box[XO] = arr->subsize;
		box[YO] = -box[XO] * box[TAN];
		arr->direction = arr->direction + 10;
	}
	return (calc_dist(arr, pv, box));
}

/* fct returns  the distance of closest wall dist_T */
float	draw_ray_minimap(t_data *arr)
{
	float		dis_v;
	float		dis_h;
	t_points	pv;
	t_points	ph;

	ph.color = WHITE;
	pv.color = WHITE;
	dis_h = dist_horizontal(&ph, arr, arr->curr_ang);
	dis_v = dist_vertical(&pv, arr, arr->curr_ang);
	if (dis_v < dis_h)
	{
		ph.x = arr->p_x;
		ph.y = arr->p_y;
		arr->image_x = pv.y % arr->subsize;
		arr->direction = arr->direction / 10;
		return (dis_v);
	}
	pv.x = arr->p_x;
	pv.y = arr->p_y;
	arr->image_x = ph.x % arr->subsize;
	arr->direction = arr->direction % 10;
	return (dis_h);
}

/* at first fct draws the floor in first call of set_line; then the ceiling*/
static void	draw_floor_ceiling(float line_h, t_data *arr, t_line *line, int r)
{
	t_points	p0;
	t_points	p1;
	float		line_o;

	line_o = (arr->height / 2) - line_h * 0.5;
	p0.color = arr->floor_rgb;
	p0.x = r;
	p0.y = arr->height;
	p1.x = p0.x;
	p1.y = line_h + line_o;
	p1.color = p0.color;
	set_line(line, arr, p0, p1);
	p0.color = arr->ceiling_rgb;
	p0.x = r;
	p0.y = line_o;
	p1.x = p0.x;
	p1.y = 0;
	p1.color = p0.color;
	set_line(line, arr, p0, p1);
}

/* check for fisheye effect then draw floor-ceiling */
void	draw_wall(t_data *arr, t_line *line, int r, float dist_t)
{
	float	ca;
	float	line_h;

	ca = arr->p_a - arr->curr_ang;
	inside_360(&ca);
	dist_t = dist_t * cos(ca);
	line_h = (arr->height * arr->subsize) / dist_t;
	draw_floor_ceiling(line_h, arr, line, r);
	draw_wall_line(line_h, arr, r);
}

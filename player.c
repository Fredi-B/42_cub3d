#include "cub3D.h"

static void	single_color_wall(t_data *arr, t_line *line, int r)
{
	t_points	p0;
	t_points	p1;

	p0.color = BLUE;
	p0.x = r;
	p0.y = 0;
	p1.x = p0.x;
	p1.y = arr->height;
	p1.color = p0.color;
	set_line(line, arr, p0, p1);
}

void	get_rays(t_data *arr, t_line *line)
{
	float		dist_t;
	int			r;

	arr->curr_ang = arr->p_a - ODR01 * 0.25 * arr->width;
	r = 0;
	while (r <= arr->width)
	{
		arr->curr_ang += ODR01 * 0.5;
		inside_360(&arr->curr_ang);
		arr->image_x = 0;
		arr->direction = 0;
		dist_t = draw_ray_minimap(arr, line);
		if (dist_t < 2)
			single_color_wall(arr, line, r);
		else
			draw_wall(arr, line, r, dist_t);
		r++;
	}
}

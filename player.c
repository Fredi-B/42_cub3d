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
	int			direction;
	int			image_start_x;
	float		ra;
	float		dist_t;
	int			r;

	ra = arr->p_a - ODR01 * 0.25 * arr->width;
	r = 0;
	while (r <= arr->width)
	{
		ra += ODR01 * 0.5;
		inside_360(&ra);
		image_start_x = 0;
		direction = 0;
		dist_t = draw_ray_minimap(&image_start_x, &direction, arr, line, ra);
		if (dist_t < 2)
			single_color_wall(arr, line, r);
		else
			draw_wall(&image_start_x, &direction, arr, line, ra, r, dist_t);
		r++;
	}
}

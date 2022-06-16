#include "cub3D.h"

/* static int	get_pixel_color_arr(t_data *arr, int x, int y)
{
	int	color;

	color = BLACK;
	if (pixel_is_inside_window(x, y, arr) == false)
		return (color);
	color = *(unsigned int *)(arr->wall[2].addr \
			+ (unsigned int)(int)y * arr->wall[2].line_length + x \
			* (arr->wall[2].bits_per_pixel / 8));
	return (color);
} */

void	get_player(t_data *arr, t_line *line)
{
	int			i;
	t_points	p0, p1;

	i = 0;
	while (i < 5) //breite 5 Grundstrich
	{
		p0.color = BLUE;
		p0.x = (arr->p_x + i - 2); // + i - 5;
		p0.y = arr->p_y - 2; // - 5;
		p1.x = p0.x;
		p1.y = arr->p_y + 2;
		p1.color = p0.color;
		set_line(line, arr, p0, p1);
		i++;
	}
/*   	i = -1;
	while (i < 1) //breite Fahne
	{
		p0.color = YELLOW;
		p0.x = arr->p_x + i ; // + i - 5;
		p0.y = arr->p_y;
		p1.x = p0.x - arr->p_dx*25;
		p1.y = p0.y - arr->p_dy*25;
		p1.color = p0.color; 
		set_line(line, arr, p0, p1);
		i++;
	} */
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
		draw_wall(&image_start_x, &direction, arr, line, ra, r, dist_t);
		r++;
	}
}

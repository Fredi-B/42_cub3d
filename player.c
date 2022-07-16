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
		// hab den player mal an einer Stelle fixiert
		// diprintf(arr->minimap_height / 2);
		// diprintf(arr->minimap_width / 2);
		
		// p0.x = (arr->minimap_width / 2) + i - 2;
		// p0.y = (arr->minimap_height / 2) - 2; // - 5;
		// p1.x = p0.x;
		// p1.y = (arr->minimap_height / 2)+ 2;
		p1.color = p0.color;
		set_line(line, arr, p0, p1);
		i++;
	}
  	i = -1;
	while (i < 5) //breite Fahne
	{
		p0.color = WHITE;
		p0.x = arr->p_x + i ; // + i - 5;
		p0.y = arr->p_y;
		p1.x = p0.x - arr->p_dx*25;
		p1.y = p0.y - arr->p_dy*25;
		p1.color = p0.color; 
		set_line(line, arr, p0, p1);
		i++;
	}
}

static void	single_color_wall(t_data *arr, t_line *line, int r)
{
	//int			i;
	t_points	p0, p1;

	//i = 0;
	//while (i < 1) //breite 5 Grundstrich
	//{
		p0.color = BLUE;
		p0.x = r;
		p0.y = 0; // - 5;
		p1.x = p0.x;
		p1.y = arr->height;
		p1.color = p0.color;
		set_line(line, arr, p0, p1);
		//i++;
	//}
}

void	make_bouquet(t_data *arr, t_line *line)
{
	t_points	p0;
	t_points	p1;
	float		ra;
	int			i;

	arr->map_flag = ON;
	p0.color = WHITE;
	p1.color = WHITE;

	p0.x = arr->p_x;
	p0.y = arr->p_y;

	ra = arr->p_a - ODR01 * 0.25 * 60;
	i = 0;
	while (i < 60)
	{
		ra += ODR01 * 0.5;
		inside_360(&ra);
		p1.x = cos(ra) * 50;
		p1.y = sin(ra) * 50;
		i++;
		printf("%d, %d\n", i, p1.x);
		set_line(line, arr, p0, p1);
	}
}


static void	draw_vision(t_data *data)
{
	int		i;
	int		j;
	int x = data->p_x;
	int y = data->p_y;

	float	ang_rad;
	t_image	*img;


	ang_rad = data->p_a * 180 / M_PI;
	img = data->img_map;
	j = 0;
	dwrite(test);
	while (j <= 41)
	{
		i = 0;
		while (i < 40)
		{
			int new_x = x + cos((ang_rad + j) * M_PI / 180) * (i);
			int new_y = y + sin((ang_rad + j) * M_PI / 180) * (i);
			if (i == 10 && j == 10)
				diprintf(new_y);
			pixel_put(data, new_x, new_y, WHITE);
			pixel_put(data, new_x, new_y, WHITE);
			i++;
		}
		j += 2;
	}
}

//0x2b2d2e
void	get_rays(t_data *arr, t_line *line)
{
	int			direction;
	int			image_start_x;
	float		ra;
	float		dist_t;
	int			r;


	ra = arr->p_a - ODR01 * 0.25 * arr->width;
	r = 0;
	// draw_vision(arr);
	while (r <= arr->width)
	{
		ra += ODR01 * 0.5;
		inside_360(&ra);
		image_start_x = 0;
		direction = 0;
		dist_t = draw_ray_minimap(&image_start_x, &direction, arr, line, ra);
		if (dist_t < 20) //too close to wall
		{
			arr->map_flag = OFF;
			single_color_wall(arr, line, r);
		}
		else
			draw_wall(&image_start_x, &direction, arr, line, ra, r, dist_t);
		r++;
	}
}

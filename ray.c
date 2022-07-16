#include "cub3D.h"

/* returns distance of ray for horizontal walls */
float	dist_horizontal(t_points *ph, t_data *arr, float ra, int *direction)
{
	float	atan;
	float	rx;
	float	ry;
	float	xo;
	float	yo;

	ph->color = WHITE;
	atan = calc_atan(ra);
	if (ra == 0 || ra == M_PI)
	{
		//ph->x = arr->p_x; ph->y=arr->p_y; dof = arr->dof;
		return (1000000);
	}
	else if (ra < M_PI)
	{
		ry = (((int)arr->p_y >> arr->sub_bit) << arr->sub_bit) - 0.0001;
		rx = (arr->p_y - ry) * atan + arr->p_x;
		yo = -arr->subsize;
		xo = -yo * atan;
		*direction = 0;
	}
	else if (ra > M_PI)
	{
		ry = (((int)arr->p_y >> arr->sub_bit) << arr->sub_bit) + arr->subsize;
		rx = (arr->p_y - ry) * atan + arr->p_x;
		yo = arr->subsize;
		xo = -yo * atan;
		*direction = 2;
	}
	return (calc_dist(arr, rx, ry, ph, xo, yo));
}

/* returns distance of ray for vertical walls */
float	dist_vertical(t_points *pv, t_data *arr, float ra, int *direction)
{
	float	ntan;
	float	rx;
	float	ry;
	float	xo;
	float	yo;

	pv->color = WHITE;
	ntan = calc_ntan(ra);
	if (ra == 0 || ra == M_PI)
	{
		return (1000000);
	}
	else if (ra < M_PI * 0.5 || ra > M_PI * 1.5)
	{
		rx = (((int)arr->p_x >> arr->sub_bit) << arr->sub_bit) - 0.0001;
		ry = (arr->p_x - rx) * ntan + arr->p_y;
		xo = -arr->subsize;
		yo = -xo * ntan;
		*direction = *direction + 30;
	}
	else if (ra > M_PI * 0.5 && ra < M_PI * 1.5)
	{
		rx = (((int)arr->p_x >> arr->sub_bit) << arr->sub_bit) + arr->subsize;
		ry = (arr->p_x - rx) * ntan + arr->p_y;
		xo = arr->subsize;
		yo = -xo * ntan;
		*direction = *direction + 10;
	}
	return (calc_dist(arr, rx, ry, pv, xo, yo));
}

/* fct returns  the distance of closest wall dist_T */
float	draw_ray_minimap(int *image_start_x, int *direction, t_data *arr, t_line *line, float ra)
{
	float		dis_v;
	float		dis_h;
	t_points	pv;
	t_points	ph;

	ph.color = WHITE;
	pv.color = WHITE;
	//returns distance of ray
	dis_h = dist_horizontal(&ph, arr, ra, direction);
	dis_v = dist_vertical(&pv, arr, ra, direction);
	//printf("dish: %f disv:%f dof %d\n",dis_h, dis_v, arr->dof);
	if (dis_v < dis_h) //RAY hits Vertical line
	{
		ph.x = arr->p_x; //set the other point
		ph.y = arr->p_y;
		*image_start_x = pv.y % arr->subsize;
		*direction = *direction / 10;
		return (dis_v);
	}
	pv.x = arr->p_x; //RAY hits horizontal line
	pv.y = arr->p_y;
	*image_start_x = ph.x % arr->subsize;
	//printf("playerh: %d %d\n",pv.x, pv.y);
	//printf("rayendh: %d! %d\n",ph.x, ph.y);
	//printf("rayendh: %d! %d\n",ph.x, ((int)ph.x % arr->subsize));
	*direction = *direction % 10;
	return (dis_h);
/* 		if (disV + 0.001 > disH && disV - 0.001 < disH) //RAY hits Corner?
		{
			direction = old_direction;
		} */
}

/* at first draws the floor in first call of set_line; then the ceiling*/
void	draw_floor_ceiling(float lineH, float lineO, t_data *arr, t_line *line, int r)
{
	t_points	p0;
	t_points	p1;

	p0.color = arr->floor_rgb;
	p0.x = r;
	p0.y = arr->height;
	p1.x = p0.x;
	p1.y = lineH + lineO;
	p1.color = p0.color;
	set_line(line, arr, p0, p1);
	p0.color = arr->ceiling_rgb;
	p0.x = r;
	p0.y = lineO;
	p1.x = p0.x;
	p1.y = 0;
	p1.color = p0.color;
	set_line(line, arr, p0, p1);
}

void	draw_wall(int *image_start_x, int *direction, t_data *arr, t_line *line, float ra, int r, float dist_t)
{
	float	ca;
	float	line_h;
	float	line_o;
	//float	dist_t;
	//t_points pv;
	//t_points ph;
	//ph.color = WHITE;
	ca = arr->p_a - ra; //fisheye start
	inside_360(&ca);
	dist_t = dist_t * cos(ca); //fisheye end
	line_h = (arr->height * arr->subsize) / dist_t; //line_height
		line_o = (arr->height / 2) - line_h * 0.5;
	draw_floor_ceiling(line_h, line_o, arr, line, r);
	//draw WALL
	//p0.color = get_wall(direction);
	//old_direction = direction;
	draw_wall_line(direction, image_start_x, line_h, arr, r);
}

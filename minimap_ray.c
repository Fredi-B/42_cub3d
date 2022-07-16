#include "cub3D.h"

//is angle inside 360 degrees?
void	inside_360(float *ra)
{
	if (*ra < 0)
		*ra += 2 * M_PI;
	if (*ra >= 2 * M_PI)
		*ra -= 2 * M_PI;
}

float	dist_vec(t_data *arr, float x, float y)
{
	return (sqrt((x - arr->p_x) * (x - arr->p_x) + \
			(y - arr->p_y) * (y - arr->p_y)));
}

float	calc_dist(t_data *arr, float rx, float ry, t_points *po, float xo, float yo)
{
	int		dof;
	int		mx;
	int		my;
	int		mp;

	dof = 0;
	while (dof < arr->dof)
	{
		//printf("mx: %d my: %d mp: %d\n",mx, my, mp);
		mx = (int)(rx) >> arr->sub_bit;
		my = (int)(ry) >> arr->sub_bit;
		mp = my * arr->cols + mx;
		//printf("map: %c my:%d mx:%d\n",arr->map[mp], my, mx);
		if (mp >= 0 && mp < arr->cols * arr->rows 
			&& (arr->map[mp] == '1' || arr->map[mp] == 'X')) //passt das besser, dass er auch bei X endet
		{
			po->x = rx;
			po->y = ry;
			return (dist_vec(arr, rx, ry));
		}
		rx += xo;
		ry += yo;
		dof++;
	}
	return (1000000);
}

float	calc_atan(float ra)
{
	if ((ra < 0.00001 && ra > -0.00001) || (ra < M_PI + 0.00001 && ra > M_PI - 0.00001))
		return (-2147483647);
	return (-1 / tan(ra));
}

float	dist_horizontal(t_points *ph, t_data *arr, float ra, int *direction) //returns distance of ray
{
	float	atan;
	float	rx;
	float	ry;
	float	xo;
	float	yo;

	ph->color = WHITE;
	atan = calc_atan(ra);
	if (ra == 0  || ra == M_PI)
	{
		//ph->x = arr->p_x; ph->y=arr->p_y; dof = arr->dof;
		return (1000000);
	}
	else if (ra < M_PI) //player schaut nach oben
	{
		ry = (((int)arr->p_y >> arr->sub_bit) << arr->sub_bit) - 0.0001;
		rx = (arr->p_y - ry) * atan + arr->p_x;
		yo = -arr->subsize;
		xo = -yo * atan;
		*direction = 0;
	}
	else if (ra > M_PI) //player schaut nach unten
	{
		ry = (((int)arr->p_y >> arr->sub_bit) << arr->sub_bit) + arr->subsize;
		rx = (arr->p_y - ry) * atan + arr->p_x;
		yo = arr->subsize;
		xo = -yo * atan;
		*direction = 2;
	}
	return (calc_dist(arr, rx, ry, ph, xo, yo));
}

float	calc_ntan(float ra)
{
	if (ra > M_PI * 0.5 - 0.00001 && ra < M_PI * 0.5)
		return (2147483647);
	else if (ra < M_PI * 0.5 + 0.00001 && ra > M_PI * 0.5)
		return (-2147483647);
	else if (ra > M_PI * 1.5 - 0.00001 && ra < M_PI * 1.5)
		return (2147483647);
	else if (ra < M_PI * 1.5 + 0.00001 && ra > M_PI * 1.5)
		return (-2147483647);
	return (-tan(ra));
}

float	dist_vertical(t_points *pv, t_data *arr, float ra, int *direction) //returns distance of ray
{
	float	ntan;
	float	rx;
	float	ry;
	float	xo;
	float	yo;

	pv->color = WHITE;
	ntan = calc_ntan(ra);
	if (ra == 0 || ra == M_PI) //player schaut oben unten
	{
		//rx = arr->p_x; ry=arr->p_y; dof = arr->dof;
		return (1000000);
	}
	else if (ra < M_PI * 0.5 || ra > M_PI * 1.5)//player schaut nach links??
	{
		rx = (((int)arr->p_x >> arr->sub_bit) << arr->sub_bit) - 0.0001;
		ry = (arr->p_x - rx) * ntan + arr->p_y;
		xo = -arr->subsize;
		yo = -xo * ntan;
		*direction = *direction + 30;
	}
	else if (ra > M_PI * 0.5 && ra < M_PI * 1.5) //player schaut nach rechts??
	{
		rx = (((int)arr->p_x >> arr->sub_bit) << arr->sub_bit) + arr->subsize;
		ry = (arr->p_x - rx) * ntan + arr->p_y;
		xo = arr->subsize;
		yo = -xo * ntan;
		*direction = *direction + 10;
	}
	return (calc_dist(arr, rx, ry, pv, xo, yo));
}

float	draw_ray_minimap(int *image_start_x, int *direction, t_data *arr, t_line *line, float ra) //return dist_T
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

void	draw_floor_ceiling(float lineH, float lineO, t_data *arr, t_line *line, int r)
{
	t_points	p0;
	t_points	p1;

	// draw FLOOR
	p0.color = arr->floor_rgb;
	p0.x = r;
	p0.y = arr->height;
	p1.x = p0.x;
	p1.y = lineH + lineO;
	p1.color = p0.color;
	set_line(line, arr, p0, p1);
	// draw CEILING
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
	//float	dist_t;
	//t_points pv;
	//t_points ph;
	//ph.color = WHITE;
	ca = arr->p_a - ra; //fisheye start
	inside_360(&ca);
	dist_t = dist_t * cos(ca); //fisheye end
	line_h = (arr->height * arr->subsize) / dist_t; //line_height

	float	line_o;
		line_o = (arr->height / 2) - line_h * 0.5;
	draw_floor_ceiling(line_h, line_o, arr, line, r);
	//draw WALL
	//p0.color = get_wall(direction);
	//old_direction = direction;
	draw_wall_line(direction, image_start_x, line_h, arr, r);
}

#include "cub3D.h"

static int	get_pixel_color_arr(t_data *arr, int x, int y)
{
	int	color;

	color = BLACK;
	if (pixel_is_inside_window(x, y, arr) == false)
		return (color);
	color = *(unsigned int *)(arr->wall[2].addr \
			+ (unsigned int)(int)y * arr->wall[2].line_length + x \
			* (arr->wall[2].bits_per_pixel / 8));
	return (color);
}

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
	int			mx, my, mp, dof, direction, wall_slice, old_direction, image_start_x;
	float		rx, ry, ra, xo, yo, dist_t, dist_T;
	int			color;
	int			r;
	t_points	p0, p1;

	ra = arr->p_a - ODR01 * 300;
	r = 0;
	while (r <= 600)
	{
		ra += ODR01;
		inside_360(&ra);


//!!!!
/* 		dof = 0;  //check Horitonal line
		float aTan;
		float disH=1000000;
		float hx, hy;
		if ((ra < 0.00001 && ra > -0.00001) || (ra < M_PI + 0.00001 && ra > M_PI - 0.00001))
			aTan = 2147483647 * -1;
		else
			aTan = -1/tan(ra);
		if (ra == 0  || ra == M_PI)
		{
			rx = arr->p_x; ry=arr->p_y; dof = arr->dof;
		}
		else if (ra < M_PI) //player schaut nach oben
		{
			ry = (((int)arr->p_y >> arr->sub_bit) << arr->sub_bit) - 0.0001;
			rx = (arr->p_y - ry) * aTan + arr->p_x;
			yo = - arr->subsize;
			xo = -yo * aTan *1;
			direction = 0;
	//printf("schaut nach oben\n");
	 //printf("ra: %f rx: %f ry: %f\n",ra, rx, ry);
	 //printf("yo: %f xo: %f aTan: %f\n",yo, xo, aTan);
		}
		else if (ra > M_PI)//player schaut nach unten
		{
			ry = (((int)arr->p_y >> arr->sub_bit) << arr->sub_bit) + arr->subsize;
			rx = (arr->p_y - ry) * aTan + arr->p_x;
			yo = arr->subsize;
			xo = -yo * aTan;
			direction = 2;
	//printf("schaut nach unten\n");
	//printf("ra: %f rx: %f ry: %f\n",ra, rx, ry);
	//printf("yo: %f xo: %f aTan: %f\n",yo, xo, aTan);
		}

		while (dof < arr->dof)
		{
			//printf("mx: %d my: %d mp: %d\n",mx, my, mp);
			mx = (int) (rx) >> arr->sub_bit;
			my = (int) (ry) >> arr->sub_bit;
			mp = my * arr->cols + mx;
			//printf("map: %c my:%d mx:%d\n",arr->map[mp], my, mx);

			if (mp >= 0 && mp < arr->cols * arr->rows && arr->map[mp] == '1')
			{
				hx = rx; hy=ry; disH=dist_vec(arr,rx,ry);
				//SAVE rx ry and distance player to ray
				dof = arr->dof;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		dof = 0;  //check vertical line
		float nTan;
		float disV=1000000;
		float vx, vy;
		if (ra > M_PI * 0.5 - 0.00001 && ra < M_PI * 0.5)
			nTan = 2147483647;
		else if (ra < M_PI * 0.5 + 0.00001 && ra > M_PI * 0.5)
			nTan = -2147483647;
		else if (ra > M_PI * 1.5 - 0.00001 && ra < M_PI * 1.5)
			nTan = 2147483647;
		else if (ra < M_PI * 1.5 + 0.00001 && ra > M_PI * 1.5)
			nTan = -2147483647;	
		else
			nTan = -tan(ra);

		//float nTan = -tan(ra);
		if (ra == 0  || ra == M_PI) //player schaut oben unten
		{
			rx = arr->p_x; ry=arr->p_y; dof = arr->dof;
		}
		else if (ra < M_PI * 0.5 || ra > M_PI * 1.5)//player schaut nach links??
		{
			rx = (((int)arr->p_x >> arr->sub_bit) << arr->sub_bit) - 0.0001;
			ry = (arr->p_x - rx) * nTan + arr->p_y;
			xo = - arr->subsize;
			yo = -xo * nTan *1;
			direction = direction + 30;

	//printf("schaut nach links\n");
	 //printf("ra: %f rx: %f ry: %f\n",ra, rx, ry);
	 //printf("yo: %f xo: %f nTan: %f\n",yo, xo, nTan);
		}
		else if (ra > M_PI * 0.5 && ra < M_PI * 1.5)//player schaut nach rechts??
		{
			rx = (((int)arr->p_x >> arr->sub_bit) << arr->sub_bit) + arr->subsize;
			ry = (arr->p_x - rx) * nTan + arr->p_y;
			xo = arr->subsize;
			yo = -xo * nTan;
			direction = direction + 10;

	//printf("schaut nach rechts\n");

	 //printf("ra: %f rx: %f ry: %f\n",ra, rx, ry);
	 //printf("yo: %f xo: %f nTan: %f\n",yo, xo, nTan);
		}
		while (dof < arr->dof)
		{
			//printf("mx: %d my: %d mp: %d\n",mx, my, mp);
			mx = (int) (rx) >> arr->sub_bit;
			my = (int) (ry) >> arr->sub_bit;
			mp = my * arr->cols + mx;
			//printf("map: %c my:%d mx:%d\n",arr->map[mp], my, mx);

			if (mp >= 0 && mp < arr->cols * arr->rows && arr->map[mp] == '1')
			{
				vx = rx; vy=ry; disV=dist_vec(arr,rx,ry);
				dof = arr->dof;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}

		p0.color = color;
		p0.x = arr->p_x;
		p0.y = arr->p_y;
		p1.color = p0.color;
	printf("dish: %f disv:%f dof %d\n",disH, disV, arr->dof);

		if (disV < disH)
		{
			p1.x = (int) vx;
			p1.y = (int) vy;
			image_start_x = p1.y;

			dist_T = disV; //RAY hits Vertical line
			direction = direction / 10;
		}
		else
		{
			p1.x = (int) hx;
			image_start_x = p1.x;
			p1.y = (int) hy;
			dist_T = disH; //RAY hits horizontal line
			direction = direction % 10;
		}
		if (disV + 0.001 > disH && disV - 0.001 < disH) //RAY hits Corner?
		{
			direction = old_direction;
		}
		printf("player: %d %d\n",p0.x, p0.y);
		printf("rayend: %d %d\n",p1.x, p1.y);
		set_line(line, arr, p0, p1); //RAY in 2D Map
 */
//!!!!!


		image_start_x = 0;
		direction = 0;
		dist_t = draw_ray_minimap(&image_start_x, &direction, arr, line, ra);
		draw_wall(&image_start_x, &direction, arr, line, ra, r, dist_t);
		r++;
	}
}

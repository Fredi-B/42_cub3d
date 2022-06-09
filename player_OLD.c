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

float	dist_vec(t_data *arr, float x, float y)
{
	return ( sqrt( (x - arr->p_x) * (x - arr->p_x) + (y - arr->p_y) * (y - arr->p_y) ));
}

void	get_player(t_data *arr, t_line *line)
{
	int		i;
	t_points p0, p1;

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
	int		r, mx, my, mp, dof, direction, wall_slice, old_direction, image_start_x;
	float	rx,ry, ra, xo, yo, dist_T;
	int		color;
	t_points p0, p1;

	wall_slice = 1; //arr->width / 60 - 1;
	color = WHITE;
	// ra= arr->p_a - ODR * 30;
	// for(r = 0; r < 60; r++)
	ra= arr->p_a - ODR01 * 300;
	for(r = 0; r <= 600; r++)
	{
		arr->map_flag = 1;
		ra += ODR01;
		
		if (ra < 0)        //inside_360???
			ra += 2 * M_PI;
		if (ra >= 2 * M_PI)
			ra -= 2 * M_PI;

 		dof = 0;  //check Horitonal line
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
		//printf("player: %d %d\n",p0.x, p0.y);
		//printf("rayend: %d %d\n",p1.x, p1.y);
		set_line(line, arr, p0, p1); //RAY in 2D Map


		float ca = arr->p_a - ra; //fisheye start
		if (ca < 0)
			ca += 2* M_PI;
		else if (ca > 2* M_PI)
			ca -= 2* M_PI;
		dist_T = dist_T * cos(ca); //fisheye end
		float lineH = (arr->height * arr->subsize)/dist_T; //lineHeight
		if (lineH > arr->height)
			lineH = arr->height;
		float lineO = (arr->height / 2) - lineH  * 0.5; //line Offset
		//printf("3D: distT:%f lineH:%f lineO:%f\n",dist_T, lineH, lineO);

		//int		i;
		//t_points p0, p1;
		arr->map_flag = 0;
		int i = 0;
		while (i < wall_slice) //eigentlich <= aber sieht man minimap nicht mehr
		{
			// draw FLOOR
			p0.color = arr->floor_rgb;
			p0.x = r *(wall_slice + 1) + i; // + i - 5;
			p0.y = arr->height; // - 5;
			p1.x = p0.x;
			p1.y = lineH + lineO;
			p1.color = p0.color;
				// p0.color = get_pixel_color_arr(arr, p0.x, p0.y);
				// p1.color = get_pixel_color_arr(arr, p1.x, p1.y);
			//printf("start3D: %d %d\n",p0.x, p0.y);
			//printf("end3D: %d %d\n",p1.x, p1.y);
			set_line(line, arr, p0, p1);
			// draw CEILING
			p0.color = arr->ceiling_rgb;
			p0.x = r *(wall_slice + 1) + i; // + i - 5;
			p0.y = lineO; //arr->height / 2; // - 5;
			p1.x = p0.x;
			p1.y = 0;
			p1.color = p0.color;
				// p0.color = get_pixel_color_arr(arr, p0.x, p0.y);
				// p1.color = get_pixel_color_arr(arr, p1.x, p1.y);
			//printf("start3D: %d %d\n",p0.x, p0.y);
			//printf("end3D: %d %d\n",p1.x, p1.y);
			set_line(line, arr, p0, p1);
			
			//!!!!
			// draw WALL
			// use image_start_x to get the color of the image at position x
			// bit shiften um nur die letzten Nummern, also alles kleiner als subsize zu bekommen?
			// Dann ist das die x_position. fuer y muss das bild genormt sein, auf die groesse der ansicht, wie?
			// dann muss entlang der Linie jede farbe rausgezogen werden und geplottet
			p0.color = get_wall(direction);
			
			old_direction = direction;
			//draw_wall_line(direction, image_start_x, lineH, arr);

			//p0.x = r *17 + arr->height / 2 + i; // + i - 5;
			p0.x = r *(wall_slice + 1) + i; // + i - 5;
			p0.y = lineO; // - 5;
			p1.x = p0.x;
			p1.y = lineH + lineO;
			p1.color = p0.color;
				// p0.color = get_pixel_color_arr(arr, p0.x, p0.y);
				// p1.color = get_pixel_color_arr(arr, p1.x, p1.y);
			//printf("start3D: %d %d\n",p0.x, p0.y);
			//printf("end3D: %d %d\n",p1.x, p1.y);
			//set_line(line, arr, p0, p1);
			// drawed WALL
			//!!!!
			i++;
		}
	}
}
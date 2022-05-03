#include "cub3D.h"

float	dist_vec(t_array *arr, float x, float y)
{
	return ( sqrt( (x - arr->p_x) * (x - arr->p_x) + (y - arr->p_y) * (y - arr->p_y) ));
}

void	get_player(t_array *arr, t_line *line)
{
	int		i;
	t_points p0, p1;

	i = 0;
	while (i < 5) //breite 5 Grundstrich
	{
		p0.color = YELLOW;
		p0.x = arr->p_x + i - 2; // + i - 5;
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

void	get_rays(t_array *arr, t_line *line)
{
	int		r, mx, my, mp, dof;
	float	rx,ry, ra, xo, yo, dist_T;
	int		color;
	t_points p0, p1;

	color = YELLOW;//0x00FFFF00;
	ra= arr->p_a - ODR * 30;
	for(r = 0; r < 30; r++)
	{
		ra += 2*ODR;
		if (ra < 0)
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
			rx = arr->p_x; ry=arr->p_y; dof = 8;
		}
		else if (ra < M_PI) //player schaut nach oben
		{
			ry = (((int)arr->p_y >> 6) << 6) - 0.0001;
			rx = (arr->p_y - ry) * aTan + arr->p_x;
			yo = -64;
			xo = -yo * aTan *1;
	//printf("schaut nach oben\n");
	 //printf("ra: %f rx: %f ry: %f\n",ra, rx, ry);
	 //printf("yo: %f xo: %f aTan: %f\n",yo, xo, aTan);
		}
		else if (ra > M_PI)//player schaut nach unten
		{
			ry = (((int)arr->p_y >> 6) << 6) + 64;
			rx = (arr->p_y - ry) * aTan + arr->p_x;
			yo = 64;
			xo = -yo * aTan;
	//printf("schaut nach unten\n");
	//printf("ra: %f rx: %f ry: %f\n",ra, rx, ry);
	//printf("yo: %f xo: %f aTan: %f\n",yo, xo, aTan);
		}

		while (dof < 8)
		{
			//printf("mx: %d my: %d mp: %d\n",mx, my, mp);
			mx = (int) (rx) >> 6;
			my = (int) (ry) >> 6;
			mp = my * arr->cols + mx;
			//printf("map: %c my:%d mx:%d\n",arr->map[mp], my, mx);

			if (mp >= 0 && mp < arr->cols * arr->rows && arr->map[mp] == '1')
			{
				hx = rx; hy=ry; disH=dist_vec(arr,rx,ry);
				//SAVE rx ry and distance player to ray
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		dof = 0;  //check verical line
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
			rx = arr->p_x; ry=arr->p_y; dof = 8;
		}
		else if (ra < M_PI * 0.5 || ra > M_PI * 1.5)//player schaut nach links??
		{
			rx = (((int)arr->p_x >> 6) << 6) - 0.0001;
			ry = (arr->p_x - rx) * nTan + arr->p_y;
			xo = -64;
			yo = -xo * nTan *1;
	//printf("schaut nach links\n");
	 //printf("ra: %f rx: %f ry: %f\n",ra, rx, ry);
	 //printf("yo: %f xo: %f nTan: %f\n",yo, xo, nTan);
		}
		else if (ra > M_PI * 0.5 && ra < M_PI * 1.5)//player schaut nach rechts??
		{
			rx = (((int)arr->p_x >> 6) << 6) + 64;
			ry = (arr->p_x - rx) * nTan + arr->p_y;
			xo = 64;
			yo = -xo * nTan;
	//printf("schaut nach rechts\n");

	 //printf("ra: %f rx: %f ry: %f\n",ra, rx, ry);
	 //printf("yo: %f xo: %f nTan: %f\n",yo, xo, nTan);
		}
		while (dof < 8)
		{
			//printf("mx: %d my: %d mp: %d\n",mx, my, mp);
			mx = (int) (rx) >> 6;
			my = (int) (ry) >> 6;
			mp = my * arr->cols + mx;
			//printf("map: %c my:%d mx:%d\n",arr->map[mp], my, mx);

			if (mp >= 0 && mp < arr->cols * arr->rows && arr->map[mp] == '1')
			{
				vx = rx; vy=ry; disV=dist_vec(arr,rx,ry);
				dof = 8;
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
			dist_T = disV; //RAY hits Vertical line
		}
		else
		{
			p1.x = (int) hx;
			p1.y = (int) hy;
			dist_T = disH; //RAY hits horizontal line
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
		float lineH = (512 * 64)/dist_T; //lineHeight
		if (lineH > 512)
			lineH = 512;
		float lineO = 256 - lineH  * 0.5; //line Offset
		//printf("3D: distT:%f lineH:%f lineO:%f\n",dist_T, lineH, lineO);

		//int		i;
		//t_points p0, p1;

		int i = 0;
		while (i < 16) //breite 5 Grundstrich
		{
			p0.color = YELLOW;
			p0.x = r *17 + 512 + i; // + i - 5;
			p0.y = lineO; // - 5;
			p1.x = p0.x;
			p1.y = lineH + lineO;
			p1.color = p0.color;
			//printf("start3D: %d %d\n",p0.x, p0.y);
			//printf("end3D: %d %d\n",p1.x, p1.y);
			set_line(line, arr, p0, p1);
			i++;
		}
	}
}

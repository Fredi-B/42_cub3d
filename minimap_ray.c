#include "cub3D.h"

//fct inside_360:
void inside_360(float *ra)
{
	if (*ra < 0)
		*ra += 2 * M_PI;
	if (*ra >= 2 * M_PI)
		*ra -= 2 * M_PI;
}


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

float	calc_dist(arr, rx, ry, po)
{
	int		dof;
	int		mx;
	int		my;
	int		mp;

	dof = 0;
	while (dof < arr->dof)
	{
		//printf("mx: %d my: %d mp: %d\n",mx, my, mp);
		mx = (int) (rx) >> arr->sub_bit;
		my = (int) (ry) >> arr->sub_bit;
		mp = my * arr->cols + mx;
		//printf("map: %c my:%d mx:%d\n",arr->map[mp], my, mx);
		if (mp >= 0 && mp < arr->cols * arr->rows && arr->map[mp] == '1')
		{
			po.x = rx; po.y=ry;
			return (dist_vec(arr,rx,ry));
		}
		rx += xo;
		ry += yo;
		dof++;
	}
	return (1000000);
}

float	calc_nTan(ra)
{
	float	nTan;

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
}

float	dist_vertical(*pv) //returns distance of ray
{
	float nTan;

	pv.color = WHITE;
	
	nTan = calc_Tan(ra)
	if (ra == 0  || ra == M_PI) //player schaut oben unten
	{
		//rx = arr->p_x; ry=arr->p_y; dof = arr->dof;
		return (1000000);
	}
	else if (ra < M_PI * 0.5 || ra > M_PI * 1.5)//player schaut nach links??
	{
		rx = (((int)arr->p_x >> arr->sub_bit) << arr->sub_bit) - 0.0001;
		ry = (arr->p_x - rx) * nTan + arr->p_y;
		xo = - arr->subsize;
		yo = -xo * nTan *1;
		direction = direction + 30;
	}
	else if (ra > M_PI * 0.5 && ra < M_PI * 1.5)//player schaut nach rechts??
	{
		rx = (((int)arr->p_x >> arr->sub_bit) << arr->sub_bit) + arr->subsize;
		ry = (arr->p_x - rx) * nTan + arr->p_y;
		xo = arr->subsize;
		yo = -xo * nTan;
		direction = direction + 10;
	}
	return(calc_dist(arr, rx, ry, po));
}


void	draw_ray_minimap(*image_start_x, direction, arr) //return dist_T
{
	float disV;
	float disH;
	t_points pv;
	t_points ph;

	ph.color = WHITE;
	disV = dist_vertical(&pv);
	disH = dist_horitontal(&ph);
	if (disV < disH) //RAY hits Vertical line
	{
		ph.x = arr->p_x; //set the other point
		ph.y = arr->p_y;
		*image_start_x = pv.y;
		set_line(line, arr, ph, pv); //draw RAY in 2D Map
		direction = direction / 10;
		return (disV); 
	}
	pv.x = arr->p_x; //RAY hits horizontal line
	pv.y = arr->p_y;
	image_start_x = ph.x;
	set_line(line, arr, ph, pv); //draw RAY in 2D Map
	direction = direction % 10;
	return (disH); 
/* 		if (disV + 0.001 > disH && disV - 0.001 < disH) //RAY hits Corner?
		{
			direction = old_direction;
		} */
}

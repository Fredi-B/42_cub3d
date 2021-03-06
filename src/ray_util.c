#include "cub3D.h"

/*is angle inside 360 degrees? if not, change by add/subtract*/
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

float	calc_dist(t_data *arr, t_points *po, float *box)
{
	int		dof;
	int		mx;
	int		my;
	int		mp;

	dof = 0;
	while (dof < arr->dof)
	{
		mx = (int)(box[RX]) >> arr->sub_bit;
		my = (int)(box[RY]) >> arr->sub_bit;
		mp = my * arr->cols + mx;
		if (mp >= 0 && mp < arr->cols * arr->rows
			&& (arr->map[mp] == '1' || arr->map[mp] == 'X'))
		{
			po->x = box[RX];
			po->y = box[RY];
			return (dist_vec(arr, box[RX], box[RY]));
		}
		box[RX] += box[XO];
		box[RY] += box[YO];
		dof++;
	}
	return (1000000);
}

float	calc_atan(float ra)
{
	if ((ra < 0.00001 && ra > -0.00001) \
		|| (ra < M_PI + 0.00001 && ra > M_PI - 0.00001))
		return (-2147483647);
	return (-1 / tan(ra));
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

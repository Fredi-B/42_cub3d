#include "cub3D.h"


void	init_arr(t_data *arr)
{
	arr->rot_x = asin(tan(M_PI / 6));
	arr->rot_y = M_PI / 4;
	arr->rot_z = M_PI / 4;
	arr->num = (int*) malloc((1000) * sizeof(int));
}

void	free_arr(t_data *arr)
{
	free(arr->num);
}

void	init_line(t_line *line)
{
	line->err = 0;
	line->e2 = 0;
	line->sx = 0;
	line->sy = 0;
	line->dx = 0;
	line->dy = 0;
	line->x0 = 0;
	line->y0 = 0;
	line->x1 = 0;
	line->y1 = 0;
}

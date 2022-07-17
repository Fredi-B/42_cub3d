#include "cub3D.h"

int	map_init(t_data *arr)
{
	arr->width = 1024;
	arr->height = 1024;
	arr->sub_bit = 6;
	arr->subsize = pow(2, arr->sub_bit);
	arr->p_x = arr->p_x * arr->subsize + (arr->subsize / 2);
	arr->p_y = arr->p_y * arr->subsize + (arr->subsize / 2);
	arr->p_dx = cos(arr->p_a);
	arr->p_dy = sin(arr->p_a);
	arr->velocity = 0.25 * arr->subsize;
	arr->start_time = 0;
	arr->finish_time = 0;
	arr->fastest_lap = 1000;
	if (arr->rows > arr->cols)
		arr->dof = arr->rows;
	else
		arr->dof = arr->cols;
	return (OK);
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

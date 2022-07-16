#include "cub3D.h"

int	map_init(t_data *arr)
{
	// Fenstergröße hard coden. first person hat nix mit der mapgröße zu tun
	arr->width = 1024; //arr->cols * arr->subsize * 2; //8 x 64 = 512
	arr->height = 1024; //arr->rows * arr->subsize;
	arr->sub_bit = 6;
	arr->subsize = pow(2, arr->sub_bit);
	arr->p_x = arr->p_x * arr->subsize + (arr->subsize / 2);
	arr->p_y = arr->p_y * arr->subsize + (arr->subsize / 2);
	arr->p_dx = cos(arr->p_a);
	arr->p_dy = sin(arr->p_a);
	//printf("row: %d,col: %d", arr->rows,arr->cols);
	if (arr->rows > arr->cols)
		arr->dof = arr->rows;
	else
		arr->dof = arr->cols;
	// diprintf(arr->cols);
	// diprintf(arr->scale_map);
	//arr->dof = 10; //erstmal standard sollte max(cols, rows) werden
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

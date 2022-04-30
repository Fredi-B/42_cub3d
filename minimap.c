#include "cub3D.h"
void read_file(t_array *arr)
{
	int map[] = {1, 1, 1, 1, 1, 1, 1, 1,
				 1, 0, 1, 0, 0, 0, 0, 1,
				 1, 0, 1, 0, 0, 0, 0, 1,
				 1, 0, 1, 0, 0, 0, 0, 1,
				 1, 0, 1, 0, 0, 1, 0, 1,
				 1, 0, 0, 0, 0, 0, 0, 1,
				 1, 0, 0, 0, 0, 0, 0, 1,
				 1, 1, 1, 1, 1, 1, 1, 1};
	
	arr->map = map;
	arr->cols = 8;
	arr->rows = 8;
	arr->p_x = 300;
	arr->p_y = 300;
	

}


int		map_init(t_array *arr)
{
read_file(arr);

printf("h");
return (OK);
}
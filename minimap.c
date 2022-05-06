#include "cub3D.h"

void read_file(t_data *arr)
{
	char map[] = {'1', '1', '1', '1', '1', '1', '1', '1',
				 '1', '0', '1', '0', '0', '0', '0', '1',
				 '1', '0', '1', '0', '0', '0', '0', '1',
				 '1', '0', '1', '0', '0', '0', '0', '1',
				 '1', '0', '1', '0', '0', '1', '0', '1',
				 '1', '0', '0', '0', '0', '0', '0', '1',
				 '1', '0', '0', '0', '0', '0', '0', '1',
				 '1', '1', '1', '1', '1', '1', '1', '1'};
	
	arr->map = ft_strdup(map);
	arr->cols = 8;
	arr->rows = 8;
	arr->subsize = 64;
	arr->p_x = 256;
	arr->p_y = 320;
	arr->p_a = ODR;// * 0.5;
	arr->p_dx = cos(arr->p_a);
	arr->p_dy = sin(arr->p_a);

	arr->width = 1024; //8 x 64 = 512
	arr->height = 512;
	
/* 	int i = 0;
	while (i < arr->subsize -1)
	{
		printf("C: %c \n", map[i]);
		i++;
	} */
}

/* Starting point for drawing a map */
int		map_init(t_data *arr)
{
	init_arr(arr);
	read_file(arr); // MEINE
	/* FREDS!!! 
	if (read_file(argv[1], &arr) == ERROR)
		return (ERROR);
 	*/
	return (OK); //will never return because of ESC exit -> key_hook -> hook-fct -> destroy window
}

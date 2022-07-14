#include "cub3D.h"

void read_file(t_data *arr)
{
	// Fenstergröße hard coden. first person hat nix mit der mapgröße zu tun
	arr->width = 1024; //arr->cols * arr->subsize * 2; //8 x 64 = 512
	arr->height = 1024; //arr->rows * arr->subsize;
	// arr->minimap_width = arr->width / 6;
	// arr->minimap_height= arr->height / 6;
	arr->sub_bit = 6;
	arr->subsize = pow(2, arr->sub_bit);
	arr->scale_map = 3;
	arr->p_x = arr->p_x * arr->subsize + (arr->subsize / 2);
	arr->p_y = arr->p_y * arr->subsize + (arr->subsize / 2);
	//arr->p_a = ODR;// * 0.5;
	arr->p_dx = cos(arr->p_a);
	arr->p_dy = sin(arr->p_a);
	//printf("row: %d,col: %d", arr->rows,arr->cols);
	if (arr->rows > arr->cols)
	{
		arr->dof = arr->rows;
		// arr->scale_map = arr->minimap_height / arr->rows;
	}
	else
	{
		arr->dof = arr->cols;
		// arr->scale_map = arr->minimap_width / arr->cols;
	}
	// diprintf(arr->minimap_width);
	// diprintf(arr->cols);
	// diprintf(arr->scale_map);
	//arr->dof = 10; //erstmal standard sollte max(cols, rows) werden

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

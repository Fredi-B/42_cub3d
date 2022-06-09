#include "cub3D.h"

unsigned int	get_wall(int direction, float line_h)
{
	if (direction == NORTH)
		return (WHITE);
	else if (direction == EAST)
		return (GREEN);
	else if (direction == SOUTH)
		return (BLUE);
	else if (direction == WEST)
		return (YELLOW);
	return (ERROR);
}

void	draw_wall_line(int direction, int image_start_x, float line_h, t_data *data, int r)
{
/* 	static t_image	pic; //nicht immer neu kalkulieren, wenn von davor ist, altes benutzen
	static old_line_h;
	static old_direction;
	int		i;

	pic = get_wall(direction, line_h)//get_wall gibt das richtige Bild in der richtigen groesse zuruck (direction gibt an, wohin man schaut), die grosse also hohe ist in lineH gespeichert
	i = 0;
	while (i < line_h)
	{
		//color = get_color at position  in pic(x=image_start_x(const), y=i);
		//pixel_put(x=r, y=i+line_h*0.5);
		i++;
	} */
	//in diesem Bild wird die posiion image_start_x gebraucht, die mit dem verhaltnis image_start_x/arr->subsize ja prozentual die pixel angibt die man bracuht
	//mit r hat man die x_position im endbild, aber y ist nicht da, gut es startet bei -lineH*0.5
return;

}

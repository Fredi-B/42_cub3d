#include "cub3D.h"

static int	get_pixel_color(t_image *original, int x, int y)
{
	int	color;

	color = YELLOW;
/* 	if (pixel_is_inside_image(x, y, original) == false) //wie kann das passieren?
		return (color); */
	color = *(unsigned int *)(original->addr \
			+ (unsigned int)(int)y * original->line_length + x \
			* (original->bits_per_pixel / 8));
	return (color);
}

static int	get_color_from_imageatx(t_image *original, int *image_start_x, float line_h, t_data *data, int r)
{
	int		color;
	float	scale;
	float	tx;
	float	ty;
	int		y;

	scale = (float) original->height / line_h;
	//scale =  line_h / original->height;
	//return 0;
	// scale braucht man bei tx nicht @arno
	tx = (float) *image_start_x / data->subsize * original->width; //* scale; //image_start muss eigentlich ein floating-point remainder sein!
	y = 0;
	ty = 0;
	while (ty < original->height) //oder +1, was passt?
	{
		ty = y * scale;
		//printf("ORGheight:%d, tx %f, ty: %f, scale: %f\n", original->height, tx, ty, scale);
		color = get_pixel_color(original, (int) tx, (int) ty);
		//(x=r, y=-line_h*0.5+y);
		pixel_put(data, r, data->height * 0.5 - line_h * 0.5 + y, color);
		y++;
	}
	return (OK); //soll man überhaupt returnen?
}

static void	adjust_startx(int *direction, int *image_start_x, t_data *data)
{
	int tmp;

	if (*direction == NORTH)
		return ;
	else if (*direction == EAST)
		return ;
	else if (*direction == SOUTH)
	{
		tmp = data->subsize - 1 - *image_start_x;
		*image_start_x = tmp;
		return ;
	}
	else if (*direction == WEST)
	{
		tmp = data->subsize - 1 - *image_start_x;
		*image_start_x = tmp;
		return ;
	}
}

void	draw_wall_line(int *direction, int *image_start_x, float line_h, t_data *data, int r) // r = s.u.
{
	(void) line_h;
	//printf("line %d", data->xpm_file[*direction].height);
	//return;
	//printf("line %d", *image_start_x);
	adjust_startx(direction, image_start_x, data);
	get_color_from_imageatx(&data->wall[*direction],image_start_x, line_h, data, r);
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

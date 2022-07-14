#include "cub3D.h"

void	move_y(t_data *arr, int sign)
{
	float	y;
	int		mx;
	int		my;
	int		mp;
	float	check_y;
	int		check_my;
	int		check_mp;
	int		distance_to_wall;

	distance_to_wall = 9;
	y = arr->p_y + arr->p_dy * sign;
	if (arr->p_a >= 0 && arr->p_a <= M_PI)
		check_y = y + (sign * distance_to_wall);
	else
		check_y = y - (sign * distance_to_wall);
	mx = (int)(arr->p_x) >> arr->sub_bit;
	my = (int)(y) >> arr->sub_bit;
	check_my = (int)(check_y) >> arr->sub_bit;
	mp = my * arr->cols + mx;
	check_mp = check_my * arr->cols + mx;
	if (arr->map[check_mp] == '0') //for bonus
		arr->p_y = y;		//for bonus
	// if (y > 0 && y < arr->height) //for mand! dachte das geht aber sturzt bei 704 ab (reagiert nicht)
	// 	arr->p_y = y;		//for mand
	//printf("y-cord: %d, %f, height: %d\n", mp, y, arr->height);
}

void	move_x(t_data *arr, int sign)
{
	float	x;
	int		mx;
	int		my;
	int		mp;
/* 	check_ vars um in if (arr->map[check_mp] == '0') die map etwas weiter vorne zu checken
	und dabei die position des players nicht zu ändern. 
	klappt soweit ganz gut, aber man kann sich über die Ecken an die Wand sneaken
	und ab und zu gab's ein zsh: killed :( 
	vllt wegen der pi werte? + 0.00001? dunno
	das gleich bei move_y() */
	float	check_x;
	int		check_mx;
	int		check_mp;
	int		distance_to_wall;

	distance_to_wall = 9;
	x = arr->p_x + arr->p_dx * sign;
	// diprintf(sign);
	// dfprintf(arr->p_a);
	if (arr->p_a >= (M_PI / 2) && arr->p_a <= (M_PI * 1.5))
		check_x = x - (sign * distance_to_wall);
	else
		check_x = x + (sign * distance_to_wall);
	mx = (int)(x) >> arr->sub_bit;
	check_mx = (int)(check_x) >> arr->sub_bit;
	my = (int)(arr->p_y) >> arr->sub_bit;
	mp = my * arr->cols + mx;
	check_mp = my * arr->cols + check_mx;
	// diprintf(mp);
	// diprintf(check_mp);
	// write(1, &arr->map[mp], 1);
	// write(1, "\ncheck: ", 8);
	// write(1, &arr->map[check_mp], 1);
	// write(1, "\n", 1);
	if (arr->map[check_mp] == '0') 		//for bonus
		arr->p_x = x; 		//for bonus
	
	//printf("x-cord: %d, %f\n", mp, x);
	move_y(arr, sign);
}

void	turn(t_data *arr, int sign)
{
	arr->p_a += 2 * ODR * sign;
	if (arr->p_a >= 2 * M_PI)
		arr->p_a -= 2 * M_PI;
	if (arr->p_a < 0)
			arr->p_a += 2 * M_PI;
	arr->p_dx = cos(arr->p_a);
	arr->p_dy = sin(arr->p_a);
}

/* uses adjusted turn() before and after move_x().
First line of turn() is replaced by a 90 degree turn in one direction before move_x() 
and in the other direction thereafter */
void	move_sideways(t_data *arr, int sign)
{
	arr->p_a += 0.5 * M_PI;
	if (arr->p_a >= 2 * M_PI)
		arr->p_a -= 2 * M_PI;
	if (arr->p_a < 0)
			arr->p_a += 2 * M_PI;
	arr->p_dx = cos(arr->p_a);
	arr->p_dy = sin(arr->p_a);
	move_x(arr, sign);
	arr->p_a -= 0.5 * M_PI;
	if (arr->p_a >= 2 * M_PI)
		arr->p_a -= 2 * M_PI;
	if (arr->p_a < 0)
			arr->p_a += 2 * M_PI;
	arr->p_dx = cos(arr->p_a);
	arr->p_dy = sin(arr->p_a);
}

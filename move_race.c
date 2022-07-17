#include "cub3D.h"

static long long	get_time(void);

void	velocity_ctrl(t_data *data)
{
	if (data->key_flag.vel_down == ON && data->velocity > 0.04 * data->subsize)
	{
		data->velocity -= 0.03 * data->subsize;
		printf("#  speed: %2imp/h  #\n", (int)data->velocity);
	}
	if (data->key_flag.vel_up == ON && data->velocity < 0.4 * data->subsize)
	{
		data->velocity += 0.03 * data->subsize;
		printf("#  speed: %2imp/h  #\n", (int)data->velocity);
	}
}

void	lap_time(t_data *data)
{
	// dfprintf(data->p_y);
	if (data->p_y > 176 && data->p_y < 208 \
		&& data->p_x >= 128 && data->p_x <= 192)
		data->start_flag = ON;
	// dfprintf(data->p_x);
	if (data->p_x > 592 && data->p_x < 608 \
		&& data->p_y >= 64 && data->p_y <= 128)
		data->finish_flag = ON;
	if (data->start_flag == ON)
	{
		data->start_flag = OFF;
		data->start_time = get_time();
		write(1, "###################\n", 20);
		write(1, "#    Let's go     #\n", 20);
		write(1, "###################\n", 20);
	}
	if (data->finish_flag == ON)
	{
		data->finish_flag = OFF;
		data->finish_time = get_time();
		write(1, "###################\n", 20);
		write(1, "#     Finish      #\n", 20);
		write(1, "###################\n", 20);
		printf("#   Lap time: %lld  #\n", data->finish_time - data->start_time);
		if (data->finish_time - data->start_time < data->fastest_lap)
			data->fastest_lap = data->finish_time - data->start_time;
		printf("# Fastest lap: %lld #\n", data->fastest_lap);
		write(1, "###################\n", 20);
	}
}

static long long	get_time(void)
{
	struct timeval	tv;
	long long		current_time;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec);
	return (current_time);
}

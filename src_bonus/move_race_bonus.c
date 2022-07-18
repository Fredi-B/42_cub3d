#include "cub3D.h"

static void	finish_lap(t_data *data);

void	velocity_ctrl(t_data *data)
{
	if (data->key_flag.vel_down == ON && data->velocity > 0.04 * data->subsize)
	{
		data->velocity -= 0.03 * data->subsize;
		printf("#    speed: %2imph    #\n", (int)data->velocity);
	}
	if (data->key_flag.vel_up == ON && data->velocity < 0.4 * data->subsize)
	{
		data->velocity += 0.03 * data->subsize;
		printf("#    speed: %2imph    #\n", (int)data->velocity);
	}
}

/* gets and prints lap time and fastest lap.
start line (3,4) and finish line (9,2) are one tile long and 16 pixels thick
(if too thin, it can be ignored, if thicker it prints it too often) */
void	lap_time(t_data *data)
{
	if (data->p_y > 176 && data->p_y < 208 \
		&& data->p_x >= 128 && data->p_x <= 192)
		data->start_flag = ON;
	if (data->p_x > 608 && data->p_x < 640 \
		&& data->p_y >= 48 && data->p_y <= 144)
		data->finish_flag = ON;
	if (data->start_flag == ON)
	{
		data->start_flag = OFF;
		data->start_seconds = get_seconds();
		data->start_milliseconds = get_milliseconds();
		write(1, "######################\n", 23);
		write(1, "#      Let's go      #\n", 23);
		write(1, "######################\n", 23);
	}
	if (data->finish_flag == ON)
		finish_lap(data);
}

static void	finish_lap(t_data *data)
{
	long long	lap_sec;
	long long	lap_millisec;

	data->finish_flag = OFF;
	data->finish_seconds = get_seconds();
	data->finish_milliseconds = get_milliseconds();
	write(1, "######################\n", 23);
	write(1, "#       Finish       #\n", 23);
	write(1, "######################\n", 23);
	lap_sec = data->finish_seconds - data->start_seconds - 1;
	lap_millisec = ((data->finish_milliseconds - data->start_milliseconds) \
				- ((data->finish_seconds - data->start_seconds) * 1000)) / 10;
	if (lap_millisec < 0)
		lap_millisec += 100;
	printf("#  Lap time: %lld.%lld   # \n", lap_sec, lap_millisec);
	if (lap_sec < data->fastest_lap_sec \
		|| (lap_sec == data->fastest_lap_sec \
		&& lap_millisec < data->fastest_lap_millisec))
	{
		data->fastest_lap_sec = lap_sec;
		data->fastest_lap_millisec = lap_millisec;
	}
	printf("# Fastest lap: %lld.%lld #\n", data->fastest_lap_sec, \
										data->fastest_lap_millisec);
	write(1, "######################\n", 23);
}

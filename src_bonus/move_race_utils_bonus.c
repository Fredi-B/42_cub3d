#include "cub3D.h"

long long	get_seconds(void)
{
	struct timeval	tv;
	long long		seconds;

	gettimeofday(&tv, NULL);
	seconds = (tv.tv_sec);
	return (seconds);
}

long long	get_milliseconds(void)
{
	struct timeval	tv;
	long long		milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (milliseconds);
}

#include "cub3D.h"

/* frees everything needed. prints out error message. exits with exit_status */
void	err_exit(t_data *data, char *msg, int len, int exit_status)
{
	(void) data;
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, msg, len);
	if (len != 0)
		write(STDERR_FILENO, "\n", 1);
	// free_data(data);
	exit(exit_status);
}
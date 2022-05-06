#include "cub3D.h"

void	free_data(t_data *data)
{
	free(data->north);
	data->north = NULL;
	free(data->south);
	data->south = NULL;
	free(data->west);
	data->west = NULL;
	free(data->east);
	data->east = NULL;
}

/* frees everything needed. prints out error message. exits with exit_status */
void	err_exit(t_data *data, char *msg, int len, int exit_status)
{
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, msg, len);
	if (len != 0)
		write(STDERR_FILENO, "\n", 1);
	(void) data;
	// free_data(data);
	exit(exit_status);
}
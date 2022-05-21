#include "cub3D.h"

//static fehlt bei allen fcts
static bool	get_walls_and_rgb(t_data *data, int fd);
static char	**get_next_splitted_line(int fd);
bool		check_textures_extensions(t_data *data);
static void	init_flag(t_input_flags *flag);

int	parsing(t_data *data, char **argv)
{
	int	fd;

	if (ft_cmp_file_extension(argv[1], ".cub", 4) == false)
		err_exit(data, "Wrong file extension", 21, 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		err_exit(data, "Could not open file", 19, 1);
	if (get_walls_and_rgb(data, fd) == false)
		err_exit(data, "Misconfiguration in file", 24, 1);
	if (read_map(data, fd) == false)
		err_exit(data, "Misconfiguration in map", 23, 1);
	if (parse_map(data) == false)
		err_exit(data, "allowed chars in map: 1, 0, space \
and one and only one of the following: N E S W", 80, 1);
	if (validate_map(data) == false)
		err_exit(data, "Map not surrounded by walls", 27, 1);
	close(fd);
	return (0);
}

/* reads file till all six data points are stored or an error occured.
calls store_data() to store them */
static bool	get_walls_and_rgb(t_data *data, int fd)
{
	t_input_flags	flag;
	char			**splitted_line;

	init_flag(&flag);
	while (flag.no != true || flag.so != true || flag.we != true \
			|| flag.ea != true || flag.ceiling != true || flag.floor != true)
	{
		splitted_line = get_next_splitted_line(fd);
		if (splitted_line == NULL)
			continue ;
		if (splitted_line[2] != NULL)
		{
			free_two_d_arr(splitted_line);
			return (false);
		}
		if (store_data(data, &flag, splitted_line) == false)
		{
			free_two_d_arr(splitted_line);
			return (false);
		}
		free_two_d_arr(splitted_line);
	}
	if (check_textures_extensions(data) == false)
		return (false);
	return (true);
}

static char	**get_next_splitted_line(int fd)
{
	char	*line;
	char	*trimmed_line;
	char	**splitted_line;

	line = get_next_line(fd);
	if (!line || line[0] == '\n')
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	trimmed_line = ft_strtrim(line, " 	\n");
	splitted_line = ft_split(trimmed_line, ' ');
	free(line);
	line = NULL;
	free(trimmed_line);
	trimmed_line = NULL;
	if (splitted_line[0] == NULL)
		return (NULL);
	return (splitted_line);
}

bool	check_textures_extensions(t_data *data)
{
	if (ft_cmp_file_extension(data->north, ".bmp", 4) == false \
		|| ft_cmp_file_extension(data->south, ".bmp", 4) == false \
		|| ft_cmp_file_extension(data->west, ".bmp", 4) == false \
		|| ft_cmp_file_extension(data->east, ".bmp", 4) == false)
		return (false);
	return (true);
}

static void	init_flag(t_input_flags *flag)
{
	flag->no = false;
	flag->so = false;
	flag->we = false;
	flag->ea = false;
	flag->ceiling = false;
	flag->floor = false;
}

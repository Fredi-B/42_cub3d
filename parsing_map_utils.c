#include "cub3D.h"

void	init_counter_and_flag(t_counter *i, bool *only_one_player_flag)
{
	*only_one_player_flag = false;
	i->tmp_x = 0;
	i->tmp_y = 0;
	i->map = 0;
	i->line = 0;
}

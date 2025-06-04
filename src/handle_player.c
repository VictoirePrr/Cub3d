#include "cub3d.h"

int	update_player_pos(t_data *data)
{
	float	old_x;
	float	old_y;

	old_x = data->player.x;
	old_y = data->player.y;
	if (data->player.move_forward)
		move_forward(data);
	if (data->player.move_backward)
		move_backward(data);
	if (data->player.move_left)
		move_left(data);
	if (data->player.move_right)
		move_right(data);
	if (data->player.rotate_left)
		rotate_left(data);
	if (data->player.rotate_right)
		rotate_right(data);
	if (old_x != data->player.x || old_y != data->player.y)
	{
		data->matrix.map[(int)old_y][(int)old_x] = '0';
		data->matrix.map[(int)data->player.y][(int)data->player.x] = 'N';
		set_up_game(data);
	}
	return (0);
}

void	set_dir(char *c, t_data *data)
{
	if (c[0] == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
	}
	else if (c[0] == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
	}
	else if (c[0] == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
	}
	else if (c[0] == 'W')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
	}
}


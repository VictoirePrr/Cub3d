#include "cub3d.h"

int	update_player_pos(t_data *data)
{
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

void	draw_player(t_data *data)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (data->matrix.map[y])
	{
		x = 0;
		while (data->matrix.map[y][x])
		{
			if (ft_strchr(PLAYER, data->matrix.map[y][x]))
			{
				data->player.x = x;
				data->player.y = y;
				set_dir(ft_strchr(PLAYER, data->matrix.map[y][x]), data);
				put_img_to_window(data, data->floor, y, x);
				put_img_to_window(data, data->img_player, y, x);
			}
			x++;
		}
		y++;
	}
}

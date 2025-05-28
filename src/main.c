#include "cub3d.h"

int	closing_game(t_data *data)
{
	if (data)
	{
		if (data->mlx && data->win)
			mlx_destroy_window(data->mlx, data->win);
		if (data->mlx)
		{
			mlx_destroy_display(data->mlx);
			free(data->mlx);
		}
	}
	ft_printf("Game closed\n");
	exit(0);
}

void	update_player_pos(t_data *data, int color)
{
	int	x;
	int	player_size;
	int	y;
	int	new_x;
	int	new_y;

	new_x = data->start_x;
	new_y = data->start_y;
	player_size = 10;
	y = 0;
	while (y < player_size)
	{
		x = 0;
		while (x < player_size)
		{
			mlx_pixel_put(data->mlx, data->win, new_x + x, new_y + y, color);
			x++;
		}
		y++;
	}
}

int	get_key(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == UP || key == W)
	{
		update_player_pos(data, 0x000000);
		data->start_y -= 1;
		update_player_pos(data, 0x00FF00);
	}
	else if (key == DOWN || key == S)
	{
		update_player_pos(data, 0x000000);
		data->start_y += 1;
		update_player_pos(data, 0x00FF00);
	}
	else if (key == LEFT || key == A)
	{
		update_player_pos(data, 0x000000);
		data->start_x -= 1;
		update_player_pos(data, 0x00FF00);
	}
	else if (key == RIGHT || key == D)
	{
		update_player_pos(data, 0x000000);
		data->start_x += 1;
		update_player_pos(data, 0x00FF00);
	}
	return (0);
}

void	draw_player(t_data *data)
{
	int	x;
	int	player_size;
	int	y;

	player_size = 10;
	x = 0;
	while (x < player_size)
	{
		y = 0;
		while (y < player_size)
		{
			mlx_pixel_put(data->mlx, data->win, data->start_x + x, data->start_y
				+ y, 0x00FF00);
			y++;
		}
		x++;
	}
}

void	open_window(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1000, 500, "Empty window");
	data->start_x = 200;
	data->start_y = 200;
	draw_player(data);
	mlx_key_hook(data->win, get_key, data);
	mlx_hook(data->win, 17, 0, closing_game, data);
	mlx_loop(data->mlx);
}

int	main(void)
{
	t_data	data;

	open_window(&data);
	return (0);
}


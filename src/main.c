#include "cub3d.h"

void	open_window(t_data *data, t_img *img, char *map)
{
	data->matrix.map = read_map(map, &data->matrix);
	if (!data->matrix.map)
		closing_game(data);
	if (data->matrix.vtl == 0 || data->matrix.htl == 0)
	{
		ft_printf("Map is empty or invalid\n");
		closing_game(data);
	}
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, XPM_HEIGHT * (data->matrix.htl),
			XPM_WIDTH * (data->matrix.vtl), "Minimap");
	init_img(data, img);
	draw_player(data);
	// init data keys before release or press....
	data->keys.up = 0;
	data->keys.down = 0;
	data->keys.left = 0;
	data->keys.right = 0;
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_loop_hook(data->mlx, update_player_pos, data);
	mlx_hook(data->win, 17, 0, closing_game, data);
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_img	img;

	(void)argc;
	(void)argv;
	open_window(&data, &img, argv[1]);
	return (0);
}

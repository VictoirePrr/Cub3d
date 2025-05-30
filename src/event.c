#include "cub3d.h"

int handle_keypress(int keycode, t_cub3d *cub3d)
{
	if (keycode == ESC)
	{
		cleanup_mlx(cub3d);
		cleanup_game(cub3d->game);
		exit(0);
	}
	return (0);
}
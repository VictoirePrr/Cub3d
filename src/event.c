#include "cub3d.h"

int	handle_keypress(int keycode, t_cub3d *cub3d)
{
	if (keycode == ESC)
		handle_close(cub3d);
	else if (keycode == W)
		printf("Forward\n");
	else if (keycode == S)
		printf("Backward\n");
	else if (keycode == A)
		printf("Left\n");
	else if (keycode == D)
		printf("Right\n");
	else if (keycode == LEFT)
		printf("Turn Left\n");
	else if (keycode == RIGHT)
		printf("Turn Right\n");
	render_frame(cub3d);
	return (0);
}

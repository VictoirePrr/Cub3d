#include "cub3d.h"

int	init_keys(t_cub3d *cub3d)
{
	cub3d->keys = malloc(sizeof(t_keys));
	if (!cub3d->keys)
		return (1);
	cub3d->keys->w = 0;
	cub3d->keys->a = 0;
	cub3d->keys->s = 0;
	cub3d->keys->d = 0;
	cub3d->keys->left = 0;
	cub3d->keys->right = 0;
	cub3d->keys->esc = 0;
	return (0);
}

void	cleanup_keys(t_cub3d *cub3d)
{
	if (cub3d && cub3d->keys)
	{
		free(cub3d->keys);
		cub3d->keys = NULL;
	}
}

int	handle_keypress(int keycode, t_cub3d *cub3d)
{
	if (keycode == ESC)
		cub3d->keys->esc = 1;
	else if (keycode == W)
		cub3d->keys->w = 1;
	else if (keycode == S)
		cub3d->keys->s = 1;
	else if (keycode == A)
		cub3d->keys->a = 1;
	else if (keycode == D)
		cub3d->keys->d = 1;
	else if (keycode == LEFT)
		cub3d->keys->left = 1;
	else if (keycode == RIGHT)
		cub3d->keys->right = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_cub3d *cub3d)
{
	if (keycode == ESC)
		cub3d->keys->esc = 0;
	else if (keycode == W)
		cub3d->keys->w = 0;
	else if (keycode == S)
		cub3d->keys->s = 0;
	else if (keycode == A)
		cub3d->keys->a = 0;
	else if (keycode == D)
		cub3d->keys->d = 0;
	else if (keycode == LEFT)
		cub3d->keys->left = 0;
	else if (keycode == RIGHT)
		cub3d->keys->right = 0;
	return (0);
}

void	process_movement(t_cub3d *cub3d)
{
	t_camera	*cam;

	cam = cub3d->camera;
	if (cub3d->keys->w)
		move_camera(cub3d, cam->dir_x * MOVE_SPEED, cam->dir_y * MOVE_SPEED);
	if (cub3d->keys->s)
		move_camera(cub3d, -cam->dir_x * MOVE_SPEED, -cam->dir_y * MOVE_SPEED);
	if (cub3d->keys->a)
		move_camera(cub3d, -cam->plane_x * MOVE_SPEED, -cam->plane_y * MOVE_SPEED);
	if (cub3d->keys->d)
		move_camera(cub3d, cam->plane_x * MOVE_SPEED, cam->plane_y * MOVE_SPEED);
	if (cub3d->keys->left)
		rotate_camera(cam, -ROTATE_SPEED);
	if (cub3d->keys->right)
		rotate_camera(cam, ROTATE_SPEED);
}

int	game_loop(t_cub3d *cub3d)
{
	if (cub3d->keys->esc)
		handle_close(cub3d);
	
	process_movement(cub3d);
	render_frame(cub3d);
	return (0);
}

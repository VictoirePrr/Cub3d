#include "cub3d.h"

void	print_camera_debug(t_camera *camera)
{
	double	angle;

	printf("=== CAMERA DEBUG ===\n");
	printf("Position: (%.3f, %.3f)\n", camera->pos_x, camera->pos_y);
	printf("Direction: (%.3f, %.3f)\n", camera->dir_x, camera->dir_y);
	printf("Plane: (%.3f, %.3f)\n", camera->plane_x, camera->plane_y);
	angle = atan2(camera->dir_y, camera->dir_x);
	if (angle < 0)
		angle += 2 * PI;
	printf("Angle: %.3f rad (%.1f°)\n", angle, angle * 180 / PI);
	printf("===================\n");
}

int	key_press(int key, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (key == ESC)
		handle_close(cub3d);
	else if (key == UP || key == W)
		cub3d->camera->move_forward = 1;
	else if (key == DOWN || key == S)
		cub3d->camera->move_backward = 1;
	else if (key == A)
		cub3d->camera->move_left = 1;
	else if (key == D)
		cub3d->camera->move_right = 1;
	else if (key == LEFT)
		cub3d->camera->rotate_left = 1;
	else if (key == RIGHT)
		cub3d->camera->rotate_right = 1;
	return (0);
}

int	key_release(int key, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (key == UP || key == W)
		cub3d->camera->move_forward = 0;
	else if (key == DOWN || key == S)
		cub3d->camera->move_backward = 0;
	else if (key == A)
		cub3d->camera->move_left = 0;
	else if (key == D)
		cub3d->camera->move_right = 0;
	else if (key == LEFT)
		cub3d->camera->rotate_left = 0;
	else if (key == RIGHT)
		cub3d->camera->rotate_right = 0;
	return (0);
}

int	handle_keypress(int keycode, t_cub3d *cub3d)
{
	if (keycode == ESC)
		handle_close(cub3d);
	else
	{
		handle_camera_movement(keycode, cub3d);
		render_frame(cub3d);
		print_camera_debug(cub3d->camera);
	}
	return (0);
}

int	update_player_pos(t_cub3d *cub3d)
{
	float	old_x;
	float	old_y;

	old_x = cub3d->camera->pos_x;
	old_y = cub3d->camera->pos_y;
	if (cub3d->camera->move_forward)
		move_forward(cub3d);
	if (cub3d->camera->move_backward)
		move_backward(cub3d);
	if (cub3d->camera->move_left)
		move_left(cub3d);
	if (cub3d->camera->move_right)
		move_right(cub3d);
	if (cub3d->camera->rotate_left)
		rotate_left(cub3d);
	if (cub3d->camera->rotate_right)
		rotate_right(cub3d);
	if (old_x != cub3d->camera->pos_x || old_y != cub3d->camera->pos_y)
	{
		cub3d->game->map->grid[(int)old_y][(int)old_x] = '0';
		cub3d->game->map->grid[(int)cub3d->camera->pos_y][(int)cub3d->camera->pos_x] = 'N';
		render_frame(cub3d);
	}
	return (0);
}

void	handle_camera_movement(int keycode, t_cub3d *cub3d)
{
	t_camera	*cam;

	cam = cub3d->camera;
	if (keycode == W)
		move_camera(cub3d, cam->dir_x * MOVE_SPEED, cam->dir_y * MOVE_SPEED);
	else if (keycode == S)
		move_camera(cub3d, -cam->dir_x * MOVE_SPEED, -cam->dir_y * MOVE_SPEED);
	else if (keycode == A)
		move_camera(cub3d, -cam->plane_x * MOVE_SPEED, -cam->plane_y
			* MOVE_SPEED);
	else if (keycode == D)
		move_camera(cub3d, cam->plane_x * MOVE_SPEED, cam->plane_y
			* MOVE_SPEED);
	else if (keycode == LEFT)
		rotate_camera(cam, -ROTATE_SPEED);
	else if (keycode == RIGHT)
		rotate_camera(cam, ROTATE_SPEED);
}

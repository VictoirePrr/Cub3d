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

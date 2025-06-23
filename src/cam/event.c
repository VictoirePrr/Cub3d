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

// int	handle_mouse(int x, int y, t_cub3d *cub3d)
// {
// 	t_camera	*cam;

// 	cam = cub3d->camera;
// 	y = 0;
// 	mlx_mouse_move(cub3d->mlx->mlx_ptr, cub3d->mlx->win_ptr, WIN_WIDTH / 2,
// 		WIN_HEIGHT / 2);
// 	if (x < cub3d->last_mouse_x)
// 		rotate_camera(cam, ROTATE_SPEED_MOUSE);
// 	else if (x > cub3d->last_mouse_x)
// 		rotate_camera(cam, -ROTATE_SPEED_MOUSE);
// 	cub3d->last_mouse_x = x;
// 	return (0);
// }

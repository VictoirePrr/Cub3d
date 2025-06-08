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

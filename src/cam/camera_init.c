#include "cub3d.h"

int	init_camera(t_cub3d *cub3d)
{
	t_player *player = cub3d->game->player;

	cub3d->camera = malloc(sizeof(t_camera));
	if (!cub3d->camera)
		return (1);

	cub3d->camera->pos_x = (double)player->x + 0.5;
	cub3d->camera->pos_y = (double)player->y + 0.5;

	set_direction_from_orientation(cub3d->camera, player->orientation);
	update_camera_plane(cub3d->camera);
	printf("Camera initialized at (%.2f, %.2f) facing %c\n",
		cub3d->camera->pos_x, cub3d->camera->pos_y, player->orientation);

	return (0);
}
void	set_direction_from_orientation(t_camera *camera, char orientation)
{
	if (orientation == 'N')
	{
		camera->dir_x = 0;
		camera->dir_y = -1;
	}
	else if (orientation == 'S')
	{
		camera->dir_x = 0;
		camera->dir_y = 1;
	}
	else if (orientation == 'E')
	{
		camera->dir_x = 1;
		camera->dir_y = 0;
	}
	else if (orientation == 'W')
	{
		camera->dir_x = -1;
		camera->dir_y = 0;
	}
}

void	update_camera_plane(t_camera *camera)
{
	double plane_distance = 0.66; // for FOV

	camera->plane_x = camera->dir_y * plane_distance;
	camera->plane_y = -camera->dir_x * plane_distance;
	printf("Camera plane set to (%.2f, %.2f)\n", camera->plane_x, camera->plane_y);
}

void	cleanup_camera(t_cub3d *cub3d)
{
	if (cub3d && cub3d->camera)
	{
		free(cub3d->camera);
		cub3d->camera = NULL;
	}
}

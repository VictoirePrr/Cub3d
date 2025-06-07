#include "cub3d.h"

int	check_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game->map->width || map_y < 0
		|| map_y >= game->map->height)
		return (1);
	return (game->map->grid[map_y][map_x] == '1');
}

void	move_camera(t_cub3d *cub3d, double move_x, double move_y)
{
	t_camera	*cam;
	double		new_x;
	double		new_y;

	cam = cub3d->camera;
	new_x = cam->pos_x + move_x;
	new_y = cam->pos_y + move_y;
	if (!check_wall(cub3d->game, new_x, cam->pos_y))
		cam->pos_x = new_x;
	if (!check_wall(cub3d->game, cam->pos_x, new_y))
		cam->pos_y = new_y;
}

void	rotate_camera(t_camera *camera, double rotation)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = camera->dir_x;
	old_plane_x = camera->plane_x;
	camera->dir_x = camera->dir_x * cos(rotation) - camera->dir_y
		* sin(rotation);
	camera->dir_y = old_dir_x * sin(rotation) + camera->dir_y * cos(rotation);
	camera->plane_x = camera->plane_x * cos(rotation) - camera->plane_y
		* sin(rotation);
	camera->plane_y = old_plane_x * sin(rotation) + camera->plane_y
		* cos(rotation);
}

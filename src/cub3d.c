#include "cub3d.h"

int	init_components(t_cub3d *cub3d, char *filename)
{
	cub3d->game = init_game();
	if (!cub3d->game)
		return (1);
	cub3d->last_mouse_x = 0;
	if (parse_file_secure(filename, cub3d->game) != 0)
	{
		cleanup_game(cub3d->game);
		return (1);
	}
	if (init_camera(cub3d) != 0)
	{
		cleanup_game(cub3d->game);
		return (1);
	}
	if (init_keys(cub3d) != 0)
	{
		cleanup_camera(cub3d);
		cleanup_game(cub3d->game);
		return (1);
	}
	return (0);
}

int	init_mlx_components(t_cub3d *cub3d)
{
	if (init_mlx(cub3d) != 0)
		return (1);
	if (create_window(cub3d) != 0)
	{
		cleanup_mlx(cub3d);
		return (1);
	}
	if (create_image(cub3d) != 0)
	{
		cleanup_mlx(cub3d);
		return (1);
	}
	if (init_textures(cub3d) != 0)
	{
		cleanup_mlx(cub3d);
		return (1);
	}
	return (0);
}

void	cleanup_mlx_error(t_cub3d *cub3d)
{
	cleanup_mlx(cub3d);
	cleanup_keys(cub3d);
	cleanup_camera(cub3d);
	cleanup_game(cub3d->game);
}

void	cleanup_error(t_cub3d *cub3d)
{
	cleanup_keys(cub3d);
	cleanup_camera(cub3d);
	cleanup_game(cub3d->game);
}

int	init_cub3d(t_cub3d *cub3d, char *filename)
{
	if (init_components(cub3d, filename) != 0)
		return (1);
	if (init_mlx_components(cub3d) != 0)
	{
		cleanup_error(cub3d);
		return (1);
	}
	print_game_info(cub3d->game);
	return (0);
}

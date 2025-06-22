#include "cub3d.h"

void	cleanup_mlx(t_cub3d *cub3d)
{
	if (!cub3d || !cub3d->mlx)
		return ;
	if (cub3d->game->north->img_ptr)
		mlx_destroy_image(cub3d->mlx->mlx_ptr, cub3d->game->north->img_ptr);
	if (cub3d->game->south->img_ptr)
		mlx_destroy_image(cub3d->mlx->mlx_ptr, cub3d->game->south->img_ptr);
	if (cub3d->game->west->img_ptr)
		mlx_destroy_image(cub3d->mlx->mlx_ptr, cub3d->game->west->img_ptr);
	if (cub3d->game->east->img_ptr)
		mlx_destroy_image(cub3d->mlx->mlx_ptr, cub3d->game->east->img_ptr);
	if (cub3d->mlx->img_ptr)
		mlx_destroy_image(cub3d->mlx->mlx_ptr, cub3d->mlx->img_ptr);
	if (cub3d->mlx->win_ptr)
		mlx_destroy_window(cub3d->mlx->mlx_ptr, cub3d->mlx->win_ptr);
	if (cub3d->mlx->mlx_ptr)
	{
		mlx_destroy_display(cub3d->mlx->mlx_ptr);
		free(cub3d->mlx->mlx_ptr);
	}
	free(cub3d->mlx);
	cub3d->mlx = NULL;
}

int	handle_close(t_cub3d *cub3d)
{
	cleanup_mlx(cub3d);
	cleanup_camera(cub3d);
	cleanup_keys(cub3d);
	cleanup_game(cub3d->game);
	exit(0);
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

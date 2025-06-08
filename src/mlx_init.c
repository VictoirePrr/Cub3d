#include "cub3d.h"

int	init_mlx(t_cub3d *cub3d)
{
	cub3d->mlx = malloc(sizeof(t_mlx));
	if (!cub3d->mlx)
		return (1);
	cub3d->mlx->mlx_ptr = mlx_init();
	if (!cub3d->mlx->mlx_ptr)
	{
		free(cub3d->mlx);
		return (1);
	}
	cub3d->mlx->win_ptr = NULL;
	cub3d->mlx->img_ptr = NULL;
	cub3d->mlx->img_data = NULL;
	return (0);
}

int	create_window(t_cub3d *cub3d)
{
	cub3d->mlx->win_ptr = mlx_new_window(cub3d->mlx->mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT, WIN_TITLE);
	if (!cub3d->mlx->win_ptr)
		return (1);
	return (0);
}

int	create_image(t_cub3d *cub3d)
{
	cub3d->mlx->img_ptr = mlx_new_image(cub3d->mlx->mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT);
	if (!cub3d->mlx->img_ptr)
		return (1);
	cub3d->mlx->img_data = mlx_get_data_addr(cub3d->mlx->img_ptr,
			&cub3d->mlx->bits_per_pixel, &cub3d->mlx->line_length,
			&cub3d->mlx->endian);
	if (!cub3d->mlx->img_data)
		return (1);
	return (0);
}

void	cleanup_mlx(t_cub3d *cub3d)
{
	if (!cub3d || !cub3d->mlx)
		return ;
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
#include "cub3d.h"

void	put_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = cub3d->mlx->img_data + (y * cub3d->mlx->line_length + x
			* (cub3d->mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render_frame(t_cub3d *cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				put_pixel(cub3d, x, y,
					cub3d->game->roof->r << 16 | cub3d->game->roof->g << 8 | cub3d->game->roof->b);
			else
				put_pixel(cub3d, x, y,
					cub3d->game->floor->r << 16 | cub3d->game->floor->g << 8 | cub3d->game->floor->b);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub3d->mlx->mlx_ptr, cub3d->mlx->win_ptr,
		cub3d->mlx->img_ptr, 0, 0);
}

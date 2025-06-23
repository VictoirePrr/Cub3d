#include "cub3d.h"

int	get_texture_color(t_textures *texture, int tex_x, int tex_y)
{
	int	pixel_index;

	if (tex_x < 0 || tex_x >= texture->width || tex_y < 0
		|| tex_y >= texture->height)
		return (0); 
	pixel_index = tex_y * (texture->line_length / 4) + tex_x;
	return (texture->data[pixel_index]);
}

void	put_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = cub3d->mlx->img_data + (y * cub3d->mlx->line_length + x
			* (cub3d->mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_rgb(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	return ((r << 16) | (g << 8) | b);
}

void	render_ceiling(t_cub3d *cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(cub3d, x, y, create_rgb(cub3d->game->roof->r,
					cub3d->game->roof->g, cub3d->game->roof->b));
			x++;
		}
		y++;
	}
}

void	render_floor(t_cub3d *cub3d)
{
	int	x;
	int	y;

	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(cub3d, x, y, create_rgb(cub3d->game->floor->r,
					cub3d->game->floor->g, cub3d->game->floor->b));
			x++;
		}
		y++;
	}
}

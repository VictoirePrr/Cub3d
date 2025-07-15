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

double	calculate_floor_ceiling_distance(int y)
{
	double	row_distance;
	int		screen_center;

	screen_center = WIN_HEIGHT / 2;
	if (y == screen_center)
		return (1000.0);
	row_distance = (double)screen_center / abs(y - screen_center);
	return (row_distance);
}

void	render_ceiling(t_cub3d *cub3d)
{
	int		x;
	int		y;
	int		base_color;
	int		final_color;
	double	distance;

	base_color = create_rgb(cub3d->game->roof->r, cub3d->game->roof->g,
			cub3d->game->roof->b);
	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		distance = calculate_floor_ceiling_distance(y);
		final_color = apply_fog(base_color, distance, 5.0, 15.0);
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(cub3d, x, y, final_color);
			x++;
		}
		y++;
	}
}

void	render_floor(t_cub3d *cub3d)
{
	int		x;
	int		y;
	int		base_color;
	int		final_color;
	double	distance;

	base_color = create_rgb(cub3d->game->floor->r, cub3d->game->floor->g,
			cub3d->game->floor->b);
	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		distance = calculate_floor_ceiling_distance(y);
		final_color = apply_fog(base_color, distance, 5.0, 15.0);
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(cub3d, x, y, final_color);
			x++;
		}
		y++;
	}
}

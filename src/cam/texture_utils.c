#include "cub3d.h"

void	calc_bounds(t_ray *ray, t_wall_params *p)
{
	p->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	p->draw_start = -p->line_height / 2 + WIN_HEIGHT / 2;
	if (p->draw_start < 0)
		p->draw_start = 0;
	p->draw_end = p->line_height / 2 + WIN_HEIGHT / 2;
	if (p->draw_end >= WIN_HEIGHT)
		p->draw_end = WIN_HEIGHT - 1;
}

double	get_wall_x(t_cub3d *cub3d, t_ray *ray)
{
	if (ray->side == 0)
		return (cub3d->camera->pos_y + ray->perp_wall_dist * ray->ray_dir_y);
	else
		return (cub3d->camera->pos_x + ray->perp_wall_dist * ray->ray_dir_x);
}

int	get_tex_x(double wall_x, t_ray *ray)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)TEXTURE_WIDTH);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		tex_x = TEXTURE_WIDTH - tex_x - 1;
	return (tex_x);
}

t_textures	*get_texture(t_cub3d *cub3d, t_ray *ray)
{
	if (ray->side == 0 && ray->ray_dir_x > 0)
		return (cub3d->game->south);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		return (cub3d->game->north);
	if (ray->side == 1 && ray->ray_dir_y > 0)
		return (cub3d->game->east);
	return (cub3d->game->west);
}

int	apply_fog(int color, double distance, double fog_start, double fog_end)
{
	double	fog_factor;
	int		r;
	int		g;
	int		b;

	if (distance <= fog_start)
		return (color);
	if (distance >= fog_end)
		return (0x404040);
	fog_factor = (distance - fog_start) / (fog_end - fog_start);
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = r * (1.0 - fog_factor) + 0x40 * fog_factor;
	g = g * (1.0 - fog_factor) + 0x40 * fog_factor;
	b = b * (1.0 - fog_factor) + 0x40 * fog_factor;
	return (create_rgb(r, g, b));
}

void	draw_column(t_cub3d *cub3d, int x, t_wall_params *p, t_textures *tex)
{
	int	y;
	int	tex_y;
	int	color;
	int	final_color;

	y = p->draw_start;
	while (y <= p->draw_end)
	{
		tex_y = (int)p->tex_pos & (TEXTURE_HEIGHT - 1);
		p->tex_pos += p->step;
		color = get_texture_color(tex, p->tex_x, tex_y);
		final_color = apply_fog(color, p->wall_distance, 5.0, 15.0);
		put_pixel(cub3d, x, y, final_color);
		y++;
	}
}

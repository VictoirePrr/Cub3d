/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicperri <vicperri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:30:19 by vicperri          #+#    #+#             */
/*   Updated: 2025/07/23 10:30:20 by vicperri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

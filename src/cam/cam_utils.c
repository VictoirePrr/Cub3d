/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicperri <vicperri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:26:02 by vicperri          #+#    #+#             */
/*   Updated: 2025/07/23 10:29:03 by vicperri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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

void	perform_ray_step(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->map_x += ray->step_x;
		ray->side_dist_x += ray->delta_dist_x;
		ray->side = 0;
	}
	else
	{
		ray->map_y += ray->step_y;
		ray->side_dist_y += ray->delta_dist_y;
		ray->side = 1;
	}
}

int	create_rgb(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	return ((r << 16) | (g << 8) | b);
}

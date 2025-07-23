/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicperri <vicperri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:30:06 by vicperri          #+#    #+#             */
/*   Updated: 2025/07/23 10:30:07 by vicperri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	should_recenter_mouse(int x, int distance_threshold)
{
	int	center_x;
	int	distance_from_center;

	center_x = WIN_WIDTH / 2;
	distance_from_center = abs(x - center_x);
	if (distance_from_center >= distance_threshold)
		return (1);
	return (0);
}

void	apply_mouse_rotation(t_camera *cam, int delta_x)
{
	if (delta_x < 0)
		rotate_camera(cam, ROTATE_SPEED_MOUSE);
	else if (delta_x > 0)
		rotate_camera(cam, -ROTATE_SPEED_MOUSE);
}

void	recenter_mouse_if_needed(t_cub3d *cub3d, int x)
{
	int	center_x;
	int	center_y;
	int	threshold;

	center_x = WIN_WIDTH / 2;
	center_y = WIN_HEIGHT / 2;
	threshold = (WIN_WIDTH * 3) / 10;
	if (should_recenter_mouse(x, threshold))
	{
		mlx_mouse_move(cub3d->mlx->mlx_ptr, cub3d->mlx->win_ptr,
			center_x, center_y);
		cub3d->last_mouse_x = center_x;
	}
	else
		cub3d->last_mouse_x = x;
}

int	handle_mouse(int x, int y, t_cub3d *cub3d)
{
	t_camera	*cam;
	int			delta_x;

	(void)y;
	cam = cub3d->camera;
	delta_x = x - cub3d->last_mouse_x;
	apply_mouse_rotation(cam, delta_x);
	recenter_mouse_if_needed(cub3d, x);
	return (0);
}

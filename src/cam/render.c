#include "cub3d.h"

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}			t_ray;

void	put_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = cub3d->mlx->img_data + (y * cub3d->mlx->line_length + x
			* (cub3d->mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_ray(t_cub3d *cub3d, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->ray_dir_x = cub3d->camera->dir_x + cub3d->camera->plane_x * camera_x;
	ray->ray_dir_y = cub3d->camera->dir_y + cub3d->camera->plane_y * camera_x;
	ray->map_x = (int)cub3d->camera->pos_x;
	ray->map_y = (int)cub3d->camera->pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

void	calculate_step_and_side_dist(t_cub3d *cub3d, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cub3d->camera->pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cub3d->camera->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cub3d->camera->pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cub3d->camera->pos_y)
			* ray->delta_dist_y;
	}
}

void	perform_dda(t_cub3d *cub3d, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (cub3d->game->map->grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	calculate_wall_distance(t_cub3d *cub3d, t_ray *ray)
{
	(void)cub3d;
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}


int	get_wall_color(t_ray *ray)
{
	int	color;

	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			color = 0xFF0000;
		else
			color = 0x800000;
	}
	else
	{
		if (ray->step_y > 0)
			color = 0x00FF00;
		else
			color = 0x008000;
	}
	if (ray->side == 1)
		color = color >> 1 & 0x7F7F7F;
	return (color);
}

void	draw_wall_line(t_cub3d *cub3d, int x, t_ray *ray)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	y;
	int	wall_color;

	line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	wall_color = get_wall_color(ray);
	y = 0;
	while (y < draw_start)
	{
		put_pixel(cub3d, x, y,
			cub3d->game->roof->r << 16 | cub3d->game->roof->g << 8 | cub3d->game->roof->b);
		y++;
	}
	while (y <= draw_end)
	{
		put_pixel(cub3d, x, y, wall_color);
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		put_pixel(cub3d, x, y,
			cub3d->game->floor->r << 16 | cub3d->game->floor->g << 8 | cub3d->game->floor->b);
		y++;
	}
}

void	cast_ray(t_cub3d *cub3d, int x)
{
	t_ray	ray;

	init_ray(cub3d, &ray, x);
	calculate_step_and_side_dist(cub3d, &ray);
	perform_dda(cub3d, &ray);
	calculate_wall_distance(cub3d, &ray);
	draw_wall_line(cub3d, x, &ray);
}

void	render_frame(t_cub3d *cub3d)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		cast_ray(cub3d, x);
		x++;
	}
	mlx_put_image_to_window(cub3d->mlx->mlx_ptr, cub3d->mlx->win_ptr,
		cub3d->mlx->img_ptr, 0, 0);
}

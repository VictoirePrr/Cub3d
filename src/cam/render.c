#include "cub3d.h"

void	walk_until_hit_wall(t_cub3d *cub3d, t_ray *ray)
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

void	draw_wall_line(t_cub3d *cub3d, int x, t_ray *ray)
{
	t_wall_params	p;
	t_textures		*texture;

	calc_bounds(ray, &p);
	p.wall_x = get_wall_x(cub3d, ray);
	p.wall_x -= floor(p.wall_x);
	p.tex_x = get_tex_x(p.wall_x, ray);
	texture = get_texture(cub3d, ray);
	p.step = 1.0 * TEXTURE_HEIGHT / p.line_height;
	p.tex_pos = (p.draw_start - WIN_HEIGHT / 2 + p.line_height / 2) * p.step;
	draw_column(cub3d, x, &p, texture);
}

void	cast_ray(t_cub3d *cub3d, int x)
{
	t_ray	ray;
	double	next_x;
	double	next_y;

	init_data(cub3d, &ray, x);
	set_ray_step(&ray, &next_x, &next_y);
	set_ray_side_dist(cub3d, &ray, next_x, next_y);
	walk_until_hit_wall(cub3d, &ray);
	calculate_wall_distance(cub3d, &ray);
	draw_wall_line(cub3d, x, &ray);
}

void	render_frame(t_cub3d *cub3d)
{
	int	x;

	render_floor(cub3d);
	render_ceiling(cub3d);
	x = 0;
	while (x < WIN_WIDTH)
	{
		cast_ray(cub3d, x);
		x++;
	}
	mlx_put_image_to_window(cub3d->mlx->mlx_ptr, cub3d->mlx->win_ptr,
		cub3d->mlx->img_ptr, 0, 0);
}

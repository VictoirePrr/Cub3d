#include "cub3d.h"
#include "sys/time.h"

int	is_wall_at_position(t_cub3d *cub3d, int x, int y)
{
	if (x < 0 || x >= cub3d->game->map->width)
		return (1);
	if (y < 0 || y >= cub3d->game->map->height)
		return (1);
	if (cub3d->game->map->grid[y][x] == '1')
		return (1);
	return (0);
}

static void	perform_ray_step(t_ray *ray)
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

void	march_ray_step_by_step(t_cub3d *cub3d, t_ray *ray)
{
	int	wall_found;
	int	steps_taken;

	wall_found = 0;
	steps_taken = 0;
	while (wall_found == 0 && steps_taken < 1000)
	{
		perform_ray_step(ray);
		steps_taken++;
		if (is_wall_at_position(cub3d, ray->map_x, ray->map_y))
		{
			wall_found = 1;
			ray->hit = 1;
		}
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
	setup_x_direction(&ray, &next_x);
	setup_y_direction(&ray, &next_y);
	set_ray_side_dist(cub3d, &ray, next_x, next_y);
	march_ray_step_by_step(cub3d, &ray);
	// walk_until_hit_wall(cub3d, &ray);
	calculate_wall_distance(cub3d, &ray);
	draw_wall_line(cub3d, x, &ray);
}

// void	print_fps(void)
// {
// 	static struct timeval	last_time = {0, 0};
// 	static int				frame_count = 0;
// 	static double			fps = 0.0;
// 	struct timeval			current_time;
// 	double					delta_time;

// 	gettimeofday(&current_time, NULL);
// 	if (last_time.tv_sec == 0)
// 	{
// 		last_time = current_time;
// 		return ;
// 	}
// 	frame_count++;
// 	delta_time = (current_time.tv_sec - last_time.tv_sec)
// 		+ (current_time.tv_usec - last_time.tv_usec) / 1000000.0;
// 	if (frame_count >= 60 || delta_time >= 1.0)
// 	{
// 		fps = frame_count / delta_time;
// 		printf("FPS: %.1f\n", fps);
// 		frame_count = 0;
// 		last_time = current_time;
// 	}
// }

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
	//print_fps();
}

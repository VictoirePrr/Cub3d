#include "cub3d.h"

typedef struct s_ray
{
	t_camera	*cam;
	double ray_dir_x; // Direction du rayon
	double		ray_dir_y;
	int map_x; // Position map
	int			map_y;
	double delta_dist_x; // Distance  intersections X
	double delta_dist_y; // Distance  intersections Y
	int hit;             // check wall
	double side_dist_x;  // Distance jusqu'à prochaine intersection X
	double side_dist_y;  // Distance jusqu'à prochaine intersection Y
	int step_x;          // Direction du pas (-1 ou 1)
	int			step_y;
	int side;              // Côté touché (0=NS, 1=EW)
	double perp_wall_dist; // Distance perpendiculaire au mur
	int line_height;       // Hauteur de la ligne
	int draw_start;        // Début de la ligne
	int draw_end;          // Fin de la ligne
}				t_ray;

void	put_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = cub3d->mlx->img_data + (y * cub3d->mlx->line_length + x
			* (cub3d->mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_ray(t_ray *ray, t_camera *cam, int x)
{
	double	camera_x;

	ray->cam = cam;
	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->ray_dir_x = cam->dir_x + cam->plane_x * camera_x;
	ray->ray_dir_y = cam->dir_y + cam->plane_y * camera_x;
	ray->map_x = (int)cam->pos_x;
	ray->map_y = (int)cam->pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

void	calculate_step_and_side_dist(t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->cam->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->cam->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->cam->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->cam->pos_y)
			* ray->delta_dist_y;
	}
}

void	debug_init_ray(t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	printf("=== DEBUG INIT_RAY pour colonne %d ===\n", x);
	printf("camera_x: %.6f\n", camera_x);
	printf("Position caméra: (%.3f, %.3f)\n", ray->cam->pos_x, ray->cam->pos_y);
	printf("Direction caméra: (%.3f, %.3f)\n", ray->cam->dir_x,
		ray->cam->dir_y);
	printf("Plan caméra: (%.3f, %.3f)\n", ray->cam->plane_x, ray->cam->plane_y);
	printf("Direction rayon: (%.6f, %.6f)\n", ray->ray_dir_x, ray->ray_dir_y);
	printf("Position map: (%d, %d)\n", ray->map_x, ray->map_y);
	printf("Delta distances: (%.6f, %.6f)\n", ray->delta_dist_x,
		ray->delta_dist_y);
	printf("Hit: %d\n", ray->hit);
	printf("=====================================\n\n");
}

void	perform_dda(t_ray *ray, t_game *game)
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
		if (ray->map_x < 0 || ray->map_x >= game->map->width || ray->map_y < 0
			|| ray->map_y >= game->map->height
			|| game->map->grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	calculate_line_height(t_ray *ray)
{
	// Calculer la distance perpendiculaire pour éviter l'effet fish-eye
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - ray->cam->pos_x + (1 - ray->step_x)
				/ 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - ray->cam->pos_y + (1 - ray->step_y)
				/ 2) / ray->ray_dir_y;
	// Calculer hauteur de la ligne
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	// Calculer les points de début et fin
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

int	get_wall_color(t_ray *ray)
{
	int	color;

	if (ray->side == 0) //
	{
		if (ray->step_x == 1)
			color = 0xFF0000; // mur Est
		else
			color = 0x00FF00; // Ouest
	}
	else
	{
		if (ray->step_y == 1)
			color = 0x0000FF; // SUD
		else
			color = 0xFFFF00; // NORD
	}
	return (color);
}

void	draw_ceiling_and_floor(t_cub3d *cub3d, int x, int draw_start,
		int draw_end)
{
	int	y;
	int	ceiling_color;
	int	floor_color;

	ceiling_color = (cub3d->game->roof->r << 16) | (cub3d->game->roof->g << 8) | cub3d->game->roof->b;
	floor_color = (cub3d->game->floor->r << 16) | (cub3d->game->floor->g << 8) | cub3d->game->floor->b;
	y = 0;
	while (y < draw_start)
	{
		put_pixel(cub3d, x, y, ceiling_color);
		y++;
	}
	y = draw_end + 1;
	while (y < WIN_HEIGHT)
	{
		put_pixel(cub3d, x, y, floor_color);
		y++;
	}
}

void	draw_wall_line(t_cub3d *cub3d, int x, t_ray *ray)
{
	int	y;
	int	color;

	color = get_wall_color(ray);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		put_pixel(cub3d, x, y, color);
		y++;
	}
}

void	render_frame(t_cub3d *cub3d)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(&ray, cub3d->camera, x);
		if (x == 0 || x == 256 || x == 512 || x == 768 || x == 1023)
			debug_init_ray(&ray, x);
		calculate_step_and_side_dist(&ray);
		perform_dda(&ray, cub3d->game);
		calculate_line_height(&ray);
		draw_ceiling_and_floor(cub3d, x, ray.draw_start, ray.draw_end);
		draw_wall_line(cub3d, x, &ray);
		x++;
	}
	mlx_put_image_to_window(cub3d->mlx->mlx_ptr, cub3d->mlx->win_ptr,
		cub3d->mlx->img_ptr, 0, 0);
}

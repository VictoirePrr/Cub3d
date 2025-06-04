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
	camera_x = 2 * x / (double)WIN_WIDTH - 1; // calcule x de l'écran
	ray->ray_dir_x = cam->dir_x + cam->plane_x * camera_x;
	ray->ray_dir_y = cam->dir_y + cam->plane_y * camera_x;
	ray->map_x = (int)cam->pos_x;
	ray->map_y = (int)cam->pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
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
		x++;
	}
	mlx_put_image_to_window(cub3d->mlx->mlx_ptr, cub3d->mlx->win_ptr,
		cub3d->mlx->img_ptr, 0, 0);
}

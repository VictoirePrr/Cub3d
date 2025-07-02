#include "cub3d.h"

void	init_data(t_cub3d *cub3d, t_ray *ray, int column)
{
	double	ratio;

	ratio = (2.0 * column / (double)WIN_WIDTH) - 1.0;
	ray->ray_dir_x = cub3d->camera->dir_x + ratio * cub3d->camera->plane_x;
	ray->ray_dir_y = cub3d->camera->dir_y + ratio * cub3d->camera->plane_y;
	ray->map_x = (int)cub3d->camera->pos_x;
	ray->map_y = (int)cub3d->camera->pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

void	calculate_wall_distance(t_cub3d *cub3d, t_ray *ray)
{
	(void)cub3d;
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

void    setup_x_direction(t_ray *ray, double *next_x)
{
    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        *next_x = ray->map_x;
    }
    else
    {
        ray->step_x = 1;
        *next_x = ray->map_x + 1.0;
    }
}

void    setup_y_direction(t_ray *ray, double *next_y)
{
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        *next_y = ray->map_y;
    }
    else
    {
        ray->step_y = 1;
        *next_y = ray->map_y + 1.0;
    }
}

// void	setup_ray_direction(t_cub3d *cub3d, t_ray *ray)
// {
// 	if (ray->ray_dir_x < 0)
// 	{
// 		ray->step_x = -1;
// 		ray->side_dist_x = (cub3d->camera->pos_x - (double)ray->map_x)
//	* ray->delta_dist_x;
// 	}
// 	else
// 	{
// 		ray->step_x = 1;
// 		ray->side_dist_x = ((double)ray->map_x + 1.0 - cub3d->camera->pos_x)
//		* ray->delta_dist_x;
// 	}

// 	if (ray->ray_dir_y < 0)
// 	{
// 		ray->step_y = -1;
// 		ray->side_dist_y = (cub3d->camera->pos_y - (double)ray->map_y)
//	* ray->delta_dist_y;
// 	}
// 	else
// 	{
// 		ray->step_y = 1;
// 		ray->side_dist_y = ((double)ray->map_y + 1.0 - cub3d->camera->pos_y)
//	* ray->delta_dist_y;
// 	}
// }

void	set_ray_side_dist(t_cub3d *cub3d, t_ray *ray, double next_x,
		double next_y)
{
	double	player_x;
	double	player_y;

	player_x = cub3d->camera->pos_x;
	player_y = cub3d->camera->pos_y;
	ray->side_dist_x = fabs((next_x - player_x) * ray->delta_dist_x);
	ray->side_dist_y = fabs((next_y - player_y) * ray->delta_dist_y);
}

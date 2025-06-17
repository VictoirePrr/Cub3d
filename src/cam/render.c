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
int	create_rgb(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0); // Return black if values are out of range
	return ((r << 16) | (g << 8) | b);
}

void	init_ray(t_cub3d *cub3d, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	// define which direction the ray will be on the screen depending on which column we are
	ray->ray_dir_x = cub3d->camera->dir_x + cub3d->camera->plane_x * camera_x;
	// the actual ray direction and how many horizontal tiles it crosses
	ray->ray_dir_y = cub3d->camera->dir_y + cub3d->camera->plane_y * camera_x;
	// same in the vertical
	ray->map_x = (int)cub3d->camera->pos_x;
	ray->map_y = (int)cub3d->camera->pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
	// did I hit a wall ? No.
}

void	calculate_step_and_side_dist(t_cub3d *cub3d, t_ray *ray)
{
	// function to give precision on WHERE exactly the ray goes on x and y absis
	if (ray->ray_dir_x < 0)
	// which border am I targeting ? if negative it is left
	{
		ray->step_x = -1;
		ray->side_dist_x = (cub3d->camera->pos_x - ray->map_x)
			* ray->delta_dist_x;
		// how far am I from the left border of my tile ?
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cub3d->camera->pos_x)
			* ray->delta_dist_x;
		// how far am I from the right border of my tile ?
	}
	if (ray->ray_dir_y < 0)
	// which border am I targeting ? if negative it is on the top
	{
		ray->step_y = -1;
		ray->side_dist_y = (cub3d->camera->pos_y - ray->map_y)
			* ray->delta_dist_y;
		// how far am I from the top border of my tile ?
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cub3d->camera->pos_y)
			* ray->delta_dist_y;
		// how far am I from the down border of my tile ?
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

void	render_floor_and_ceiling(t_cub3d *cub3d)
{
	int	x;
	int	y;

	// Render ceiling
	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(cub3d, x, y, create_rgb(cub3d->game->roof->r,
					cub3d->game->roof->g, cub3d->game->roof->b));
			x++;
		}
		y++;
	}
	// Render floor
	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(cub3d, x, y, create_rgb(cub3d->game->floor->r,
					cub3d->game->floor->g, cub3d->game->floor->b));
			x++;
		}
		y++;
	}
}

void	draw_wall_line(t_cub3d *cub3d, int x, t_ray *ray)
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	double		step;
	double		tex_pos;
	int			color;
	t_textures	*texture;
	int			y;

	line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	// Determine wall_x (position on the wall)
	if (ray->side == 0)
		wall_x = cub3d->camera->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = cub3d->camera->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	// Calculate texture X coordinate
	tex_x = (int)(wall_x * (double)TEXTURE_WIDTH);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		tex_x = TEXTURE_WIDTH - tex_x - 1;
	// Select texture based on wall direction
	if (ray->side == 0 && ray->ray_dir_x > 0)
		texture = cub3d->game->south; // South
	else if (ray->side == 0 && ray->ray_dir_x < 0)
		texture = cub3d->game->north; // North
	else if (ray->side == 1 && ray->ray_dir_y > 0)
		texture = cub3d->game->east; // East
	else
		texture = cub3d->game->west; // West
	// Calculate step and initial texture position
	step = 1.0 * TEXTURE_HEIGHT / line_height;
	tex_pos = (draw_start - WIN_HEIGHT / 2 + line_height / 2) * step;
	// Draw the wall slice
	y = draw_start;
	while (y <= draw_end)
	{
		tex_y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
		tex_pos += step;
		// Get color from texture
		color = get_texture_color(texture, tex_x, tex_y);
		// Draw pixel
		put_pixel(cub3d, x, y, color);
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

int	get_texture_color(t_textures *texture, int tex_x, int tex_y)
{
	int	pixel_index;

	// Ensure the texture coordinates are within bounds
	if (tex_x < 0 || tex_x >= texture->width || tex_y < 0
		|| tex_y >= texture->height)
		return (0); // Return black if out of bounds
	// Calculate the pixel index in the texture data array
	pixel_index = tex_y * (texture->line_length / 4) + tex_x;
	// Return the color at the specified pixel
	return (texture->data[pixel_index]);
}

void	render_frame(t_cub3d *cub3d)
{
	int	x;

	// Render floor and ceiling
	render_floor_and_ceiling(cub3d);
	// Render walls
	x = 0;
	while (x < WIN_WIDTH)
	{
		cast_ray(cub3d, x);
		x++;
	}
	// Display the frame
	mlx_put_image_to_window(cub3d->mlx->mlx_ptr, cub3d->mlx->win_ptr,
		cub3d->mlx->img_ptr, 0, 0);
}

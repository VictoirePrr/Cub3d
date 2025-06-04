#include "cub3d.h"

void	put_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = cub3d->mlx->img_data + (y * cub3d->mlx->line_length + x
			* (cub3d->mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render_mini_map(t_cub3d *cub3d, t_game *game, int y, int x)
{
	int		tile_size;
	int		player_size;
	int		draw_x;
	int		draw_y;
	char	map;

	map = game->map->grid[y][x];
	if (map == FLOOR)
		put_img_to_window(cub3d, game->mini_map->floor.image, y, x);
	if (map == WALL)
		put_img_to_window(cub3d, game->mini_map->wall.image, y, x);
	if (ft_strchr(PLAYER, map))
	{
		// First update player position and direction
		cub3d->camera->pos_x = x;
		cub3d->camera->pos_y = y;
		// Then draw floor and player at the correct position
		put_img_to_window(cub3d, game->mini_map->floor.image, y, x);
		tile_size = 64;
		player_size = 16; // Match the actual player image size
		draw_x = x * tile_size + (tile_size - player_size) / 2;
		draw_y = y * tile_size + (tile_size - player_size) / 2;
		mlx_put_image_to_window(cub3d->mlx->mlx_ptr, cub3d->mlx->win_ptr , game->mini_map->img_player.image,
			draw_x, draw_y);
	}
}

void	render_frame(t_cub3d *cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (cub3d->game->map->grid[y] < WIN_HEIGHT) //--> parcourir la matrice !!!!!!!!!!!!!
	{
		x = 0;
		while (cub3d->game->map->grid[x] < WIN_WIDTH)
		{
			render_mini_map(cub3d, cub3d->game, y, x);
			// if (y < WIN_HEIGHT / 2)
			// 	put_pixel(cub3d, x, y,
			// 		cub3d->game->roof->r << 16 | cub3d->game->roof->g << 8 | cub3d->game->roof->b);
			// else
			// 	put_pixel(cub3d, x, y,
			// 		cub3d->game->floor->r << 16 | cub3d->game->floor->g << 8 | cub3d->game->floor->b);
			x++;
		}
		y++;
	}
	// mlx_put_image_to_window(cub3d->mlx->mlx_ptr, cub3d->mlx->win_ptr,
	// 	cub3d->mlx->img_ptr, 0, 0);
}

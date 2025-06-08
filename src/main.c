#include "cub3d.h"
#include "pars.h"

void	print_game_info(t_game *game)
{
	ft_printf("=== PARSING SUCCESSFUL ===\n");
	ft_printf("North texture: %s\n", game->textures->north);
	ft_printf("South texture: %s\n", game->textures->south);
	ft_printf("West texture: %s\n", game->textures->west);
	ft_printf("East texture: %s\n", game->textures->east);
	ft_printf("Floor color: R:%d G:%d B:%d\n", game->floor->r, game->floor->g,
		game->floor->b);
	ft_printf("Ceiling color: R:%d G:%d B:%d\n", game->roof->r, game->roof->g,
		game->roof->b);
	ft_printf("Player position: X:%d Y:%d\n", game->player->x, game->player->y);
	ft_printf("Player orientation: %c\n", game->player->orientation);
}

int	init_cub3d(t_cub3d *cub3d, char *filename)
{
	cub3d->game = init_game();
	if (!cub3d->game)
		return (1);
	if (parse_file_secure(filename, cub3d->game) != 0)
	{
		cleanup_game(cub3d->game);
		return (1);
	}
	if (init_camera(cub3d) != 0)
	{
		cleanup_game(cub3d->game);
		return (1);
	}
	if (init_keys(cub3d) != 0)
	{
		cleanup_camera(cub3d);
		cleanup_game(cub3d->game);
		return (1);
	}
	if (init_mlx(cub3d) != 0)
	{
		cleanup_keys(cub3d);
		cleanup_camera(cub3d);
		cleanup_game(cub3d->game);
		return (1);
	}
	if (create_window(cub3d) != 0 || create_image(cub3d) != 0)
	{
		cleanup_mlx(cub3d);
		cleanup_keys(cub3d);
		cleanup_camera(cub3d);
		cleanup_game(cub3d->game);
		return (1);
	}
	print_game_info(cub3d->game);
	return (0);
}

int	validate_args(int argc)
{
	if (argc != 2)
	{
		ft_printf("Error: Usage: ./cub3D map.cub\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (argc != 2)
	{
		printf("Error: Usage: ./cub3D map.cub\n");
		return (1);
	}
	if (init_cub3d(&cub3d, argv[1]) != 0)
		return (1);
	render_frame(&cub3d);
	mlx_hook(cub3d.mlx->win_ptr, 2, 1L << 0, handle_keypress, &cub3d);
	mlx_hook(cub3d.mlx->win_ptr, 3, 1L << 1, handle_keyrelease, &cub3d);
	mlx_hook(cub3d.mlx->win_ptr, 17, 0, handle_close, &cub3d);
	mlx_loop_hook(cub3d.mlx->mlx_ptr, game_loop, &cub3d);
	mlx_loop(cub3d.mlx->mlx_ptr);
	return (0);
}

// https://docs.google.com/document/d/1tdNYHg3Mfqf8dr8W6Ajs3seUugwtmaQizZ7BzimkXog/edit?tab=t.0
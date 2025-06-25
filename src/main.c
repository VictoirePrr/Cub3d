#include "cub3d.h"
#include "pars.h"

void	print_game_info(t_game *game)
{
	ft_printf("=== PARSING SUCCESSFUL ===\n");
	ft_printf("North texture: %s\n", game->north->filename);
	ft_printf("South texture: %s\n", game->south->filename);
	ft_printf("West texture: %s\n", game->west->filename);
	ft_printf("East texture: %s\n", game->east->filename);
	ft_printf("Floor color: R:%d G:%d B:%d\n", game->floor->r, game->floor->g,
		game->floor->b);
	ft_printf("Ceiling color: R:%d G:%d B:%d\n", game->roof->r, game->roof->g,
		game->roof->b);
	ft_printf("Player position: X:%d Y:%d\n", game->player->x, game->player->y);
	ft_printf("Player orientation: %c\n", game->player->orientation);
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
	mlx_hook(cub3d.mlx->win_ptr, 6, 1L << 6, handle_mouse, &cub3d);
	mlx_loop_hook(cub3d.mlx->mlx_ptr, game_loop, &cub3d);
	mlx_loop(cub3d.mlx->mlx_ptr);
	return (0);
}

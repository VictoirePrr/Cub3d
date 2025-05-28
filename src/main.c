#include "pars.h"

void	print_game_info(t_game *game)
{
	ft_printf("=== PARSING SUCCESSFUL ===\n");
	ft_printf("North texture: %s\n", game->textures->north);
	ft_printf("South texture: %s\n", game->textures->south);
	ft_printf("West texture: %s\n", game->textures->west);
	ft_printf("East texture: %s\n", game->textures->east);
	ft_printf("Floor color: R:%d G:%d B:%d\n", game->floor->r,
		game->floor->g, game->floor->b);
	ft_printf("Ceiling color: R:%d G:%d B:%d\n", game->roof->r,
		game->roof->g, game->roof->b);
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
	t_game	*game;
	int		result;

	if (validate_args(argc))
		return (1);
	game = init_game();
	if (!game)
	{
		ft_printf("Error: Memory allocation failed\n");
		return (1);
	}
	result = parse_file_secure(argv[1], game);
	if (result != 0)
	{
		cleanup_game(game);
		return (1);
	}
	print_game_info(game);
	cleanup_game(game);
	return (0);
}
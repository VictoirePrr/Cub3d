#include "pars.h"

int	init_substructures(t_game *game)
{
	game->north = ft_calloc(1, sizeof(t_textures));
	game->south = ft_calloc(1, sizeof(t_textures));
	game->west = ft_calloc(1, sizeof(t_textures));
	game->east = ft_calloc(1, sizeof(t_textures));
	game->floor = ft_calloc(1, sizeof(t_colors));
	game->roof = ft_calloc(1, sizeof(t_colors));
	game->map = ft_calloc(1, sizeof(t_map));
	game->player = ft_calloc(1, sizeof(t_player));
	if (!game->north || !game->south || !game->west || !game->east)
		return (0);
	if (!game->floor || !game->roof || !game->map || !game->player)
		return (0);
	return (1);
}

void	init_colors(t_game *game)
{
	game->floor->r = -1;
	game->floor->g = -1;
	game->floor->b = -1;
	game->roof->r = -1;
	game->roof->g = -1;
	game->roof->b = -1;
}

t_game	*init_game(void)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (NULL);
	if (!init_substructures(game))
	{
		cleanup_game(game);
		return (NULL);
	}
	init_colors(game);
	return (game);
}

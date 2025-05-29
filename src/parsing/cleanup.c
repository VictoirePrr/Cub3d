#include "pars.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	cleanup_textures(t_textures *textures)
{
	if (!textures)
		return ;
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
	free(textures);
}

void	cleanup_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		i = 0;
		while (i < map->height && map->grid[i])
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	cleanup_textures(game->textures);
	if (game->floor)
		free(game->floor);
	if (game->roof)
		free(game->roof);
	cleanup_map(game->map);
	if (game->player)
		free(game->player);
	free(game);
}

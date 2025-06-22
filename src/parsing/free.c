#include "pars.h"

void	free_map_lines(t_map_line *head)
{
	t_map_line	*current;
	t_map_line	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->line);
		free(current);
		current = next;
	}
}

int	allocate_grid(t_game *game)
{
	int	i;

	game->map->grid = malloc(sizeof(char *) * (game->map->height + 1));
	if (!game->map->grid)
		return (error_return("Memory allocation failed"));
	i = 0;
	while (i < game->map->height)
	{
		game->map->grid[i] = malloc(sizeof(char) * (game->map->width + 1));
		if (!game->map->grid[i])
		{
			while (--i >= 0)
				free(game->map->grid[i]);
			free(game->map->grid);
			game->map->grid = NULL;
			return (error_return("Memory allocation failed"));
		}
		i++;
	}
	game->map->grid[game->map->height] = NULL;
	return (0);
}
